#include "Log.h"
#include "Event.h"

#include <stdarg.h>

static Event<LogType, const char*> gLog;

#ifndef NDEBUG
static void DefaultLog(LogType type, const char *fmt)
{
  if (type == LogType::Log)
  {
    fprintf(stdout, "%s", fmt);
  }
  else
  {
    fprintf(stderr, "%s", fmt);
  }
}
#endif

void AddLogger(void (*func)(LogType, const char *))
{
  gLog += func;
}

void RemoveLogger(void (*func)(LogType, const char *))
{
  gLog -= func;
}

void Log(LogType type, const char *fmt, ...)
{
  const int bufSize = 128;
  char buf[bufSize];
  char *buffer = buf;
  
  va_list args;
  va_start(args, fmt);
  int len = vsnprintf(buffer, bufSize, fmt, args);
  if (len > bufSize) 
  {
    buffer = new char[len];
    vsnprintf(buffer, len, fmt, args);
  }
  va_end(args);  
 
#ifndef NDEBUG
  DefaultLog(type, buffer);
#endif
  
  gLog.Invoke(type, buffer);
  
  if (buffer != buf)
  {
    delete[] buffer;
  }
  
}



