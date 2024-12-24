#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class CpuSpec{
public:
    std::string name;
    int core;
    double frequency;

    CpuSpec(std::string p_name = "Unknown", int p_core = 0, double p_frequency = 0.0)
    {
        name = p_name; 
        core = p_core;
        frequency = p_frequency;
    }

    void Print() const {
        std::cout << "------------------\n"<< "CPU" << std::endl;
        std::cout << "Name: " << name << ", Cores: " << core << ", Frequency: " << frequency << " GHz" << std::endl;
    }

    void Import(std::istream& in) {
        in >> name >> core >> frequency;
    }

    void Export(std::ostream& out) const {
        out << name << " " << core << " " << frequency << std::endl;
    }
};

class GpuSpec {
public:
    std::string name;
    int memory;

    GpuSpec(std::string p_name = "Unknown", int p_memory = 0)
    {
        name = p_name;
        memory = p_memory;
    }

    void Print() const {
        std::cout << "------------------\n" << "GPU" <<  std::endl;
        std::cout << "Name: " << name << ", Memory: " << memory << " MB" << std::endl;
    }

    void Import(std::istream& in) {
        in >> name >> memory;
    }

    void Export(std::ostream& out) const {
        out << name << " " << memory << std::endl;
    }
};

class LanSpec {
public:
    std::string interface;
    int speed;

    LanSpec(std::string p_interface = "Unknown", int p_speed = 0) 
    {
        interface = p_interface;
        speed = p_speed;
    }

    void Print() const {
        std::cout << "------------------\n" << "LAN" << std::endl;
        std::cout << "Interface: " << interface << ", Speed: " << speed << " Mbps" << std::endl;
    }

    void Import(std::istream& in) {
        in >> interface >> speed;
    }

    void Export(std::ostream& out) const {
        out << interface << " " << speed << std::endl;
    }
};

class RamSpec {
public:
    std::string name;
    int size;

    RamSpec(std::string p_name = "Unknown", int p_size = 0) 
    {
        name = p_name;
        size = p_size; 
    }

    void Print() const {
        std::cout << "------------------\n"<< "RAM" <<  std::endl;
        std::cout << "Name: " << name << ", Size: " << size << " MB" << std::endl;
    }

    void Import(std::istream& in) {
        in >> name >> size;
    }

    void Export(std::ostream& out) const {
        out << name << " " << size << std::endl;
    }
};

class ClusterNode {
public:
    CpuSpec cpu;
    GpuSpec gpu;
    RamSpec ram;
    LanSpec lan;

    ClusterNode(CpuSpec p_cpu, GpuSpec p_gpu, RamSpec p_ram, LanSpec p_lan) 
    {
        cpu = p_cpu;
        gpu = p_gpu; 
        ram = p_ram;
        lan = p_lan; 
    }

    void Print(int idx = -1) const {
        if (idx == -1){
            std::cout << "Cluster" << std::endl;
        }else{
            std::cout << "Cluster #" << idx << std::endl;
        }
        cpu.Print();
        gpu.Print();
        ram.Print();
        lan.Print();
    }

    void Import(std::istream& in) {
        cpu.Import(in);
        gpu.Import(in);
        ram.Import(in);
        lan.Import(in);
    }

    void Export(std::ostream& out) const {
        cpu.Export(out);
        gpu.Export(out);
        ram.Export(out);
        lan.Export(out);
    }
};

class Cluster {
public:
    std::vector<ClusterNode> nodes;

    void AddNode(const ClusterNode& node) {
        nodes.push_back(node);
    }

    void Print() const {
        std::cout << nodes.size() << " nodes:\n";

        for (int i = 0; i < nodes.size(); i++){
            nodes[i].Print(i);
            std::cout << "==================\n";
        }
    }

    void Import(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }
        int nodeCount;
        file >> nodeCount;
        for (int i = 0; i < nodeCount; ++i) {
            CpuSpec cpu;
            GpuSpec gpu;
            RamSpec ram;
            LanSpec lan;    
            cpu.Import(file);
            gpu.Import(file);
            ram.Import(file);
            lan.Import(file);
            nodes.emplace_back(cpu, gpu, ram, lan);
        }
    }

    void Export(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file) {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }
        file << nodes.size() << std::endl;
        for (const ClusterNode& node : nodes) {
            node.Export(file);
        }
        file.close();
    }
};



int main() {
    Cluster cluster;

    ClusterNode node1(CpuSpec("Intel_i9", 8, 3.6), GpuSpec("NVIDIA_RTX_3080", 10240), RamSpec("Kingston", 32768), LanSpec("Ethernet", 100));
    ClusterNode node2(CpuSpec("AMD_Ryzen_7", 12, 3.8), GpuSpec("NVIDIA_RTX_3070", 8192), RamSpec("Kingston", 16384), LanSpec("WiFi", 10));

    cluster.AddNode(node1);
    cluster.AddNode(node2);

    cluster.Export("out.txt");

    Cluster importedCluster;
    importedCluster.Import("out.txt");

    importedCluster.Print();

    return 0;
}