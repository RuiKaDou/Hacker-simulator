#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <netdb.h>
    #include <unistd.h>
    #include <arpa/inet.h>
#endif

class HackerDeveloperTool {
private:
    std::vector<std::string> ipList;

    // Generate random IP address
    std::string generateRandomIP() {
        std::srand(std::time(nullptr) + rand());
        return std::to_string(rand() % 256) + "." +
               std::to_string(rand() % 256) + "." +
               std::to_string(rand() % 256) + "." +
               std::to_string(rand() % 256);
    }

    // Get local IP address
    std::string getLocalIP() {
        std::string localIP = "127.0.0.1";
        
        #ifdef _WIN32
            WSADATA wsaData;
            if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
                return localIP;
            }
        #endif

        char hostbuffer[256];
        struct hostent* host_entry;
        
        if (gethostname(hostbuffer, sizeof(hostbuffer)) == 0) {
            host_entry = gethostbyname(hostbuffer);
            if (host_entry != nullptr) {
                struct in_addr** addr_list = (struct in_addr**)host_entry->h_addr_list;
                if (addr_list[0] != nullptr) {
                    localIP = inet_ntoa(*addr_list[0]);
                }
            }
        }

        #ifdef _WIN32
            WSACleanup();
        #endif
        
        return localIP;
    }

    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

public:
    HackerDeveloperTool() {
        std::srand(std::time(nullptr));
    }

    void displayMainPage() {
        clearScreen();
        std::cout << "\n";
        std::cout << "╔══════════════════════════════════════════════════════╗\n";
        std::cout << "║                                                      ║\n";
        std::cout << "║     WELCOME TO HACKER DEVELOPER TOOL v1.0           ║\n";
        std::cout << "║                                                      ║\n";
        std::cout << "╚══════════════════════════════════════════════════════╝\n";
        std::cout << "\n";
        std::cout << "  ┌─────────────────────────────────────────────────┐\n";
        std::cout << "  │                 MAIN MENU                       │\n";
        std::cout << "  └─────────────────────────────────────────────────┘\n";
        std::cout << "\n";
        std::cout << "      [1] IP Finder - Generate multiple IPs\n";
        std::cout << "      [2] Port Scanner\n";
        std::cout << "      [3] Network Information\n";
        std::cout << "      [0] Exit\n";
        std::cout << "\n";
        std::cout << "  ┌─────────────────────────────────────────────────┐\n";
        std::cout << "  >> Enter your choice: ";
    }

    void ipFinder() {
        clearScreen();
        int numIPs;
        
        std::cout << "\n";
        std::cout << "╔══════════════════════════════════════════════════════╗\n";
        std::cout << "║                 IP FINDER MODULE                     ║\n";
        std::cout << "╚══════════════════════════════════════════════════════╝\n";
        std::cout << "\n";
        std::cout << "  How many IP addresses do you want to generate? ";
        std::cin >> numIPs;
        
        if (numIPs <= 0) {
            std::cout << "\n  [!] Invalid number! Please enter a positive number.\n";
        } else if (numIPs > 1000) {
            std::cout << "\n  [!] Maximum limit is 1000 IPs. Generating 1000 IPs instead.\n";
            numIPs = 1000;
        } else {
            std::cout << "\n  [✓] Generating " << numIPs << " IP address(es)...\n";
        }
        
        std::cout << "\n  ┌─────────────────────────────────────────────────┐\n";
        std::cout << "  │                  GENERATED IPS                    │\n";
        std::cout << "  └─────────────────────────────────────────────────┘\n\n";
        
        ipList.clear();
        for (int i = 0; i < numIPs; i++) {
            std::string ip = generateRandomIP();
            ipList.push_back(ip);
            std::cout << "      " << std::setw(3) << (i + 1) << ". " << ip << "\n";
        }
        
        std::cout << "\n  ┌─────────────────────────────────────────────────┐\n";
        std::cout << "  │  Total IPs generated: " << numIPs << "                      │\n";
        std::cout << "  └─────────────────────────────────────────────────┘\n";
        
        std::cout << "\n  Press Enter to return to main menu...";
        std::cin.ignore();
        std::cin.get();
    }

    void portScanner() {
        clearScreen();
        std::cout << "\n";
        std::cout << "╔══════════════════════════════════════════════════════╗\n";
        std::cout << "║                 PORT SCANNER MODULE                  ║\n";
        std::cout << "╚══════════════════════════════════════════════════════╝\n";
        std::cout << "\n";
        std::cout << "  [i] This is a demo port scanner.\n";
        std::cout << "  [i] Enter target IP to scan ports (1-1024):\n\n";
        std::cout << "  Target IP: ";
        
        std::string targetIP;
        std::cin >> targetIP;
        
        std::cout << "\n  Scanning " << targetIP << "...\n\n";
        
        // Simulate port scanning
        std::cout << "  ┌─────────────────────────────────────────────────┐\n";
        std::cout << "  │                 OPEN PORTS                      │\n";
        std::cout << "  └─────────────────────────────────────────────────┘\n\n";
        
        // Simulate finding some open ports
        std::vector<int> commonPorts = {21, 22, 23, 25, 53, 80, 110, 143, 443, 993, 995, 3306, 3389, 8080};
        for (int port : commonPorts) {
            if (rand() % 3 == 0) { // Randomly show some ports as open for demo
                std::cout << "      Port " << port << " - OPEN\n";
            }
        }
        
        std::cout << "\n  [i] Port scanning completed (Demo mode).\n";
        std::cout << "\n  Press Enter to return to main menu...";
        std::cin.ignore();
        std::cin.get();
    }

    void networkInfo() {
        clearScreen();
        std::cout << "\n";
        std::cout << "╔══════════════════════════════════════════════════════╗\n";
        std::cout << "║              NETWORK INFORMATION MODULE              ║\n";
        std::cout << "╚══════════════════════════════════════════════════════╝\n";
        std::cout << "\n";
        std::cout << "  ┌─────────────────────────────────────────────────┐\n";
        std::cout << "  │                 SYSTEM NETWORK INFO              │\n";
        std::cout << "  └─────────────────────────────────────────────────┘\n\n";
        
        std::cout << "      Local IP Address: " << getLocalIP() << "\n";
        std::cout << "      Hostname: " << getHostname() << "\n";
        std::cout << "      OS Type: ";
        #ifdef _WIN32
            std::cout << "Windows\n";
        #else
            std::cout << "Unix/Linux\n";
        #endif
        
        std::cout << "\n  [i] Network information retrieved successfully.\n";
        std::cout << "\n  Press Enter to return to main menu...";
        std::cin.ignore();
        std::cin.get();
    }

    std::string getHostname() {
        char hostname[256];
        if (gethostname(hostname, sizeof(hostname)) == 0) {
            return std::string(hostname);
        }
        return "Unknown";
    }

    void run() {
        int choice;
        do {
            displayMainPage();
            std::cin >> choice;
            
            switch (choice) {
                case 1:
                    ipFinder();
                    break;
                case 2:
                    portScanner();
                    break;
                case 3:
                    networkInfo();
                    break;
                case 0:
                    clearScreen();
                    std::cout << "\n╔══════════════════════════════════════════════════════╗\n";
                    std::cout << "║           Thank you for using Hacker Developer!       ║\n";
                    std::cout << "║                    Goodbye!                          ║\n";
                    std::cout << "╚══════════════════════════════════════════════════════╝\n\n";
                    break;
                default:
                    std::cout << "\n  [!] Invalid choice! Please try again.\n";
                    std::cout << "  Press Enter to continue...";
                    std::cin.ignore();
                    std::cin.get();
            }
        } while (choice != 0);
    }
};

int main() {
    HackerDeveloperTool tool;
    tool.run();
    return 0;
}
