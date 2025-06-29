#ifdef _WIN32
#include <windows.h> // For Sleep() on Windows
#else
#include <unistd.h> // For sleep() and usleep() on POSIX systems
#endif

void cross_platform_sleep_ms(unsigned int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds); // Windows uses milliseconds
#else
    // POSIX systems typically use seconds for sleep() or microseconds for usleep()
    // Convert milliseconds to microseconds for usleep()
    usleep(milliseconds * 1000); 
#endif
}
void sleep_seconds(float seconds)
{
    cross_platform_sleep_ms(seconds * 1000);
}