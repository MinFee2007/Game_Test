#ifndef SYSTEM_LOG_H
#define SYSTEM_LOG_H

#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>

#include "i_subsystem.h"
#include "system_all.h"
#include "system_time.h"

enum messageType{
    ERROR,
    WARNING,
    NOTIFICATION,
    OTHER
};

class LogSystem:public ISubSystem{
    private:
    std::string logpath="run.log";
    std::vector<std::string> msgtypes={
        "Error: ",
        "Warning: ",
        "Notification: ",
        "Undefined message: "
    };
    std::ofstream logfile;
    public:
    void init() override;
    void update() override;
    void destruct() override;
    bool write(messageType msgtype,const std::string& content);
    void clear();
};

#endif