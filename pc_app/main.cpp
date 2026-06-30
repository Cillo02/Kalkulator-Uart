#include <iostream>
#include <fstream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <chrono>
#include <thread>

bool configureSerial(int fd) {
    struct termios tty;

    if (tcgetattr(fd, &tty) != 0) {
        return false;
    }

    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);

    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_iflag = 0;

    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 10;

    return tcsetattr(fd, TCSANOW, &tty) == 0;
}

std::string readLine(int fd) {
    std::string response;
    char c;

    auto start = std::chrono::steady_clock::now();

    while (true) {
        int n = read(fd, &c, 1);

        if (n > 0) {
            if (c == '\n') {
                break;
            }
            response += c;
        }

        auto now = std::chrono::steady_clock::now();
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();

        if (seconds > 3) {
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return response;
}

std::ofstream openLogFile() {
    std::ofstream logFile("logs/communication_log.txt", std::ios::app);

    if (!logFile.is_open()) {
        logFile.open("../logs/communication_log.txt", std::ios::app);
    }

    return logFile;
}

int main() {
    std::string port;
    std::string input;

    std::cout << "Seriellen Port eingeben, z.B. /dev/cu.usbmodem1101: ";
    std::getline(std::cin, port);

    int fd = open(port.c_str(), O_RDWR | O_NOCTTY | O_SYNC);

    if (fd < 0) {
        std::cout << "Fehler: Serieller Port konnte nicht geöffnet werden." << std::endl;
        return 1;
    }

    if (!configureSerial(fd)) {
        std::cout << "Fehler: Serielle Schnittstelle konnte nicht konfiguriert werden." << std::endl;
        close(fd);
        return 1;
    }

    std::ofstream logFile = openLogFile();

    if (!logFile.is_open()) {
        std::cout << "Warnung: Protokolldatei konnte nicht geöffnet werden." << std::endl;
    }

    std::cout << "UART-Kalkulator gestartet." << std::endl;
    std::cout << "Zum Beenden q eingeben." << std::endl;

    while (true) {
        std::cout << "\nAusdruck eingeben, z.B. 34*72: ";
        std::getline(std::cin, input);

        if (input == "q") {
            break;
        }

        std::string message = input + "\n";

        write(fd, message.c_str(), message.length());
        if (logFile.is_open()) {
            logFile << "Gesendet: " << input << std::endl;
        }

        std::string result = readLine(fd);

        std::cout << "Antwort vom Mikrocontroller: " << result << std::endl;
        if (logFile.is_open()) {
            logFile << "Empfangen: " << result << std::endl;
        }
    }

    close(fd);
    logFile.close();

    return 0;
}
