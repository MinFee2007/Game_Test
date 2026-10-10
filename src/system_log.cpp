#include "system_log.h"
void LogSystem::init(){
    logfile.open(logpath,std::ios::out|std::ios::app); // Open and only append to the log file content
    logfile<<"Notification: Log system is initialized successfully\n";
}
void LogSystem::update(){}
void LogSystem::destruct(){
    if (logfile.is_open()){
        logfile<<"Notification: Log system is destructed\n";
        logfile.close();
    }
}
bool LogSystem::write(messageType msgtype,const std::string& content){
    size_t typeIndex=static_cast<size_t>(msgtype);
    if (typeIndex>=msgtypes.size()){ // Check if the msgtype is valid. If not, make it undefined message
        typeIndex=OTHER;
    }
    TimeSystem* timesys=AllSystem::getInstance().getSubSystem<TimeSystem>();
    if (!timesys){
        if (logfile.is_open()){
            logfile<<msgtypes[ERROR]<<"Log system is unable to access time system\n";
            logfile<<msgtypes[typeIndex]<<content<<"\n";
            logfile.flush();
        }
        return false;
    }
    SDL_DateTime dt=timesys->getDateTime(); // Get date and time from time system
    if (!logfile.is_open()){
        return false; // Check if the log file is opened
    }
    logfile<<std::setfill('0')
           <<std::setw(4)<<dt.year<<"-"
           <<std::setw(2)<<dt.month<<"-"
           <<std::setw(2)<<dt.day<<" "
           <<std::setw(2)<<dt.hour<<":"
           <<std::setw(2)<<dt.minute<<":"
           <<std::setw(2)<<dt.second<<" "
           <<msgtypes[typeIndex]<<content<<"\n";
    logfile.flush();
    return true;
}
void LogSystem::clear(){
    if (logfile.is_open()) {
        logfile.close();
    }
    logfile.open(logpath,std::ios::out|std::ios::trunc); // Reopen but truncate the file content to clear it
}