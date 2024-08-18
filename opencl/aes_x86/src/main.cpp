#define CL_TARGET_OPENCL_VERSION 300
#define __CL_HPP_ENABLE_EXCEPTIONS

#include "CL/opencl.hpp"
#include <vector>
#include <cstdint>
#include <iostream> 
#include <fstream>
#include <sstream>
#include <chrono>

#include "aes.hpp"

int main(){
    //get all platforms (drivers)
    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);
    if(all_platforms.size()==0){
        std::cout<<" No platforms found. Check OpenCL installation!\n";
        exit(1);
    }
    cl::Platform default_platform=all_platforms[0];
    std::cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";
 
    //get default device of the default platform
    std::vector<cl::Device> all_devices;
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if(all_devices.size()==0){
        std::cout<<" No devices found. Check OpenCL installation!\n";
        exit(1);
    }
   
    cl::Device default_device=all_devices[0];
    std::cout<< "Using device: "<<default_device.getInfo<CL_DEVICE_NAME>()<<"\n";
 
 
    cl::Context context({default_device});
 
    cl::Program::Sources sources;
 
    // kernel calculates for each element panded
    std::ifstream kernelFile("../kernels/aes.cl", std::ios::in);
    std::stringstream strStream;
    
    std::string kernelCode;
    if(kernelFile.is_open()){
        strStream << kernelFile.rdbuf();
        kernelCode = strStream.str();
    }
    sources.push_back({kernelCode.c_str(), kernelCode.size()});
    cl::Program program(context,sources);
    if(program.build({default_device})!=CL_SUCCESS){
        std::cout<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<<"\n";
        exit(1);
    }

    //create queue to which we will push commands for the device.
    cl::CommandQueue queue(context,default_device);

    // Buffers
    std::vector<uint8_t>expandedKey(44*4);
    std::vector<uint8_t>message = {
            0x32, 0x88, 0x31, 0xE0,
            0x43, 0x5A, 0x31, 0x37, 
            0xF6, 0x30, 0x98, 0x07,
            0xA8, 0x8D, 0xA2, 0x34};


    std::vector<uint8_t> key = {
            0x2B, 0x28, 0xAB, 0x09,
            0x7E, 0xAE, 0xF7, 0xCF,
            0x15, 0xD2, 0x15, 0x4F,
            0x16, 0xA6, 0x88, 0x3C};
    
    
    /*
     * Nr = number of rounds
     * Nk = number of words of the key
     * Nb = number of words in a state (for this standard Nb=4) 
     */
    uint8_t Nk, Nb, Nr;
    Nb = 4;
    switch(key.size()){
        case (sizeof(uint32_t)*4):
            Nk = 4;
            Nr = 10;
            break;
        case (sizeof(uint32_t)*6):
            Nk = 6;
            Nr = 12;
            break;
        case (sizeof(uint32_t)*8):
            Nk = 8;
            Nr = 14;
            break;
        default:
            throw std::runtime_error("Length of key unrecognized");
            break;
    }
   
    /********** Key expansion ***********/

    

    // copy the original key
    uint8_t keyIndex = 0;
    for(int i = 0; i<16;i++){
        expandedKey[i] = key[i];
    }

 
    std::vector<uint8_t> output(message.size());
    // create buffers on the device

    cl::Buffer buffer_message(context,CL_MEM_READ_WRITE, sizeof(uint8_t)*message.size());
    cl::Buffer buffer_key(context, CL_MEM_READ_ONLY, sizeof(uint8_t)*key.size());
    cl::Buffer buffer_expandedKey(context, CL_MEM_READ_WRITE, sizeof(uint8_t)*expandedKey.size());
    cl::Buffer buffer_sBox(context, CL_MEM_READ_ONLY, sizeof(uint8_t)*sBox.size());
    cl::Buffer buffer_mixMatrix(context, CL_MEM_READ_ONLY, sizeof(uint8_t)*mixMatrix.size());
    cl::Buffer buffer_output(context,CL_MEM_READ_WRITE, sizeof(uint8_t)*message.size());
    cl::Buffer buffer_rcon(context, CL_MEM_READ_ONLY, sizeof(uint32_t)*Rcon.size());

    //write arrays A and B to the device
    queue.enqueueWriteBuffer(buffer_message,CL_TRUE,0,sizeof(uint8_t)*message.size(),message.data());
    queue.enqueueWriteBuffer(buffer_key, CL_TRUE,0, sizeof(uint8_t)*key.size(), key.data());
    queue.enqueueWriteBuffer(buffer_expandedKey, CL_TRUE, 0, sizeof(uint8_t)*expandedKey.size(), expandedKey.data());
    queue.enqueueWriteBuffer(buffer_sBox, CL_TRUE,0, sizeof(uint8_t)*sBox.size(), sBox.data()); 
    queue.enqueueWriteBuffer(buffer_mixMatrix, CL_TRUE,0, sizeof(uint8_t)*mixMatrix.size(), mixMatrix.data());
    queue.enqueueWriteBuffer(buffer_output,CL_TRUE,0,sizeof(uint8_t)*message.size(),output.data());
    queue.enqueueWriteBuffer(buffer_rcon,CL_TRUE,0,sizeof(uint32_t)*Rcon.size(),Rcon.data());

    //queue.enqueueWriteBuffer(buffer_output, CL_TRUE, 0, sizeof(uint8_t)*16, output);
    //run the kernel
    /*cl::KernelFunctor simple_add(cl::Kernel(program,"simple_add"),queue,cl::NullRange,cl::NDRange(10),cl::NullRange);
    simple_add(buffer_A,buffer_B,buffer_C);
    */
    //alternative way to run the kernel
    cl::Kernel kernel_aes=cl::Kernel(program,"aes");
  
    kernel_aes.setArg(0,buffer_message);
    kernel_aes.setArg(1,buffer_expandedKey);
    kernel_aes.setArg(2,buffer_sBox);
    kernel_aes.setArg(3,buffer_mixMatrix);
    kernel_aes.setArg(4,buffer_output);
    kernel_aes.setArg(5,buffer_rcon);

    std::chrono::duration<double> elapsed_seconds{0};
        

    std::chrono::duration<double> total_seconds{0};
    for(uint16_t i=0; i<1000; i++){
        message = {
                0x32, 0x88, 0x31, 0xE0,
                0x43, 0x5A, 0x31, 0x37, 
                0xF6, 0x30, 0x98, 0x07,
                0xA8, 0x8D, 0xA2, 0x34};
        for(uint8_t j=0;j<16;j++){
            output[j] = 0;
        }

        kernel_aes.setArg(0,buffer_message);
        kernel_aes.setArg(4,buffer_output);

        const auto start{std::chrono::steady_clock::now()};
        queue.enqueueNDRangeKernel(kernel_aes,cl::NullRange,cl::NDRange(4,4),cl::NullRange);
        queue.finish();
        const auto end{std::chrono::steady_clock::now()};

        const std::chrono::duration<double> elapsed_seconds{end-start};
        std::cout << "Kernel i(" << (uint32_t)i << ") took: ";
        std::cout << elapsed_seconds.count();
        total_seconds += elapsed_seconds;
        std::cout << " sec to finish\n";
    }

    std::cout << "Total: " << total_seconds.count()/1000 << std::endl;
    
    /*
    //read result C from the device to array C
    queue.enqueueReadBuffer(buffer_output,CL_TRUE,0,sizeof(uint8_t)*message.size(),output.data());
    queue.enqueueReadBuffer(buffer_message,CL_TRUE,0,sizeof(uint8_t)*message.size(),message.data());
    queue.enqueueReadBuffer(buffer_expandedKey,CL_TRUE,0,sizeof(uint8_t)*expandedKey.size(),expandedKey.data());
 
    std::cout<<" message: \n";
    for(int i = 0; i<4;i++){
        for(int j=0;j<4;j++){
            std::cout << std::hex << (uint32_t)message[i*4+j];
        }
        std::cout << std::endl;
    }
    */
    return 0;
}
