//
// Created by Kegan Hollern on 12/23/23.
//

#ifndef MEMSTREAM_PROCESS_H
#define MEMSTREAM_PROCESS_H

namespace memstream {

    class Process {
    public:
        explicit Process(uint32_t pid);
        explicit Process(const std::string& name);

        Process(FPGA *pFPGA, uint32_t pid);
        Process(FPGA *pFPGA, const std::string& name);

        virtual ~Process();

        virtual bool Read(uint64_t addr, uint8_t *buffer, uint32_t size);
        virtual bool ReadMany(std::vector<std::tuple<uint64_t, uint8_t*, uint32_t>> &readOps);

        virtual bool Write(uint64_t addr, uint8_t *buffer, uint32_t size);

        virtual uint64_t GetModuleBase(const std::string& name);
        virtual bool GetModuleInfo(const std::string& name, VMMDLL_MAP_MODULEENTRY& info);
        virtual std::vector<VMMDLL_MAP_MODULEENTRY> GetModules();
        virtual std::vector<VMMDLL_MAP_EATENTRY> GetExports(const std::string& name);
        virtual std::vector<VMMDLL_MAP_IATENTRY> GetImports(const std::string& name);
        virtual std::vector<VMMDLL_MAP_THREADENTRY> GetThreads();

        virtual uint64_t FindPattern(
                uint64_t start,
                uint64_t stop,
                uint8_t *pattern,
                uint8_t *mask);

        virtual uint64_t FindCave(
                uint64_t start,
                uint64_t stop);

        // Dump(disk_path)
        // Execute(fnc, args...) rax
        // Hook ?
        // Threads ?

    private:
        VMMDLL_PROCESS_INFORMATION info;
        FPGA* pFPGA;
    public:
        bool isIs64Bit() const;
        uint32_t getPid() const;

    };

} // memstream

#endif //MEMSTREAM_PROCESS_H
