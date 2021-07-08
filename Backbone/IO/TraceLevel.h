#ifndef TRACELEVEL_H
#define TRACELEVEL_H

enum class TraceLevel {CRITICAL = 0, ERR, WARN, INFO, DEBUG, TRACE};

inline std::ostream& operator << (std::ostream& stm, TraceLevel level)
{
    switch(level)
    {
        case TraceLevel::CRITICAL : return stm << "CRITICAL";
        case TraceLevel::ERR      : return stm << "ERR";
        case TraceLevel::WARN     : return stm << "WARN";
        case TraceLevel::INFO     : return stm << "INFO";
        case TraceLevel::DEBUG    : return stm << "DEBUG";
        case TraceLevel::TRACE    : return stm << "TRACE";
        default : return stm << "TraceLevel{" << int(level) << "}"; 
    }
}

inline std::string get_name(TraceLevel level) 
{
  switch (level) 
  {
    case TraceLevel::CRITICAL : return std::string("CRITICAL");
    case TraceLevel::ERR      : return std::string("ERR");
    case TraceLevel::WARN     : return std::string("WARN");
    case TraceLevel::INFO     : return std::string("INFO");
    case TraceLevel::DEBUG    : return std::string("DEBUG");
    case TraceLevel::TRACE    : return std::string("TRACE");
    default : return std::string("");
  }
}

inline TraceLevel operator++(TraceLevel& x) 
{ 
    return x = (TraceLevel)(((int)(x) + 1)); 
}

inline TraceLevel operator*(TraceLevel c) 
{
    return c;
}

inline TraceLevel begin(TraceLevel r) 
{
    return TraceLevel::CRITICAL;
}

inline TraceLevel end(TraceLevel r)   
{
    return TraceLevel(int(TraceLevel::TRACE) + 1);
}


#endif