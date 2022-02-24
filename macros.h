

#define LOG_NOBR(FMT,...) fprintf(stdout,"%s:%d(%s) " FMT , __FILE__ , __LINE__ , __func__ , ##__VA_ARGS__ )
#define LOG(FMT,...) LOG_NOBR(FMT "\n", ##__VA_ARGS__ )
#define FATAL(FMT,...) LOG(FMT,##__VA_ARGS__),exit(1)
#define COUNT(ARR) (sizeof(ARR)/sizeof(ARR[0]))


