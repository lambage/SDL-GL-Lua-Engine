/* 
 * File:   Log.h
 * Author: daddy
 *
 * Created on September 28, 2013, 9:03 AM
 */

#ifndef LOG_H
#define	LOG_H

enum class LogType
{
    Log,
    Error,
    Warning
};

void AddLogger(void (*func)(LogType, const char *));
void RemoveLogger(void (*func)(LogType, const char *));
void Log(LogType type, const char *fmt, ...);

void SetDefaultLog();
void RemoveDefaultLog();

#endif	/* LOG_H */

