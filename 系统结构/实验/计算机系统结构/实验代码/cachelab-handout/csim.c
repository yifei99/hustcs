#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "cachelab.h"

#define ADDRESS_LENGTH 64//地址长度
typedef unsigned long long int mem_addr;//内存地址
typedef struct cache_line//cache行结构
{
    char valid;
    mem_addr tag;
    unsigned long long int lru;//LRU是一个用于实现LRU替换策略的计数器
} cache_line_t;

typedef cache_line_t* cache_set_t;//表示一个cache组
typedef cache_set_t* cache_t;//表示多个cache组构成的一个完整cache

int verbosity=0;//print trace if set
int s=0;//pow(2,s)表示有多少组
int b=0;//内存块内地址位数
int E=0;//关联度
char* trace_file=NULL;
int S=0;//S=pow(2,s)，表示有多少组
int B=0;//字节数
int miss_count=0;
int hit_count=0;
int eviction_count=0;

cache_t cache;//模拟的cache
mem_addr set_index_mask;//用于做与运算

void initCache(){
    int i,j;
    cache=(cache_set_t*)malloc(sizeof(cache_set_t)*S);//组×组数
   for(i=0;i<S;i++){
     cache[i]=(cache_line_t*) malloc(sizeof(cache_line_t) * E);
       for(j=0;j<E;j++){
           cache[i][j].valid=0;
           cache[i][j].tag=0;
           cache[i][j].lru=0;
       }
   }
     set_index_mask=(mem_addr)(pow(2,s)-1);//用来做与运算得到一个内存地址对应组编号
}

void freeCache(){
    int i;
    for(i=0;i<S;i++){
        free(cache[i]);
    }
    free(cache);
}

void accessData(mem_addr addr){
    int i;
    int evicted_line=0;
    unsigned long long int evicted_lru=0;
    mem_addr set_index=(addr>>b)&set_index_mask;//得到组编号
    mem_addr tag=addr>>(s+b);//放在一个cache行里面的tag
    int hit=0;
    cache_set_t cache_set=cache[set_index];//提取出组
    for(i=0;i<E;i++){
    //E:每一个组内有几块
        if(cache_set[i].tag==tag&&cache_set[i].valid==1){
            //在cache内
            printf("hit ");
            hit_count++;
            cache_set[i].lru=0;
            hit=1;
        }
        else if(cache_set[i].valid==1){
            cache_set[i].lru++;
        }
    }
    //未命中
    if(hit==0){
        printf("miss ");
        int j;
        miss_count++;
        for(j=0;j<E;j++){
            if(cache_set[j].valid==0){
                //未使用过，空闲位置
                evicted_line=j;
                break;
            }
            else if(cache_set[j].lru>evicted_lru){
                evicted_lru=cache_set[j].lru;
                evicted_line=j;
            }
        }
    
    if(!(cache_set[evicted_line].valid==0)){
        //有淘汰
        printf("eviction ");
        eviction_count++;
    }
    cache_set[evicted_line].valid=1;
    cache_set[evicted_line].lru=0;
    cache_set[evicted_line].tag=tag;
}
}

void replayTrace(char* trace_fn)
{
    mem_addr addr=0;
    unsigned int len=0;
    FILE* trace_fp = fopen(trace_fn, "r");
	char operation= fgetc(trace_fp);
	
	while(operation != EOF )
	{
		switch(operation)
		{	
			case 'M':{		
						fscanf(trace_fp,"%X,%d",(unsigned int*)&addr,&len);
                        printf("%c %x %u ",operation,(int)addr,len);
						accessData(addr);
                        accessData(addr);
                        printf("\n");
                        break;
			}
			case 'L':{
				        fscanf(trace_fp,"%X,%d",(unsigned int*)&addr,&len);
                        printf("%c %x %u ",operation,(int)addr,len);
                        accessData(addr);
                        printf("\n");
                        break;
			}
			case 'S':{
						fscanf(trace_fp,"%X,%d",(unsigned int*)&addr,&len);
                        printf("%c %x %u ",operation,(int)addr,len);
                        accessData(addr);
                        printf("\n");
                        break;
			}
			case 'I':{
						fscanf(trace_fp,"%X,%d",(unsigned int*)&addr,&len);//不处理
						printf("%c %x %u ",operation,(int)addr,len);
                        printf("\n");	
                        break;
			}
			default:break;
		}
        operation = fgetc(trace_fp);
	}
}

void printUsage(char* argv[])
{
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\nExamples:\n");
    printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n", argv[0]);
    printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", argv[0]);
    exit(0);
}

int main(int argc, char* argv[])
{
   char c;
    while( (c=getopt(argc,argv,"s:E:b:t:vh")) != -1){
        switch(c){
        case 's':
            s = atoi(optarg);
            break;
        case 'E':
            E = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 't':
            trace_file = optarg;
            break;
        case 'v':
            verbosity = 1;
            break;
        case 'h':
            printUsage(argv);
            exit(0);
        default:
            printUsage(argv);
            exit(1);
        }
    }
    if (s == 0 || E == 0 || b == 0 || trace_file == NULL) {
        printf("%s: Missing required command line argument\n", argv[0]);
        printUsage(argv);
        exit(1);
    }
    S = (unsigned int) pow(2, s);
    B = (unsigned int) pow(2, b);
    initCache();
#ifdef  DEBUG_ON
    printf("DEBUG: S:%u E:%u B:%u trace:%s\n", S, E, B, trace_file);
    printf("DEBUG: set_index_mask: %llu\n", set_index_mask);
#endif
    replayTrace(trace_file);
    freeCache();
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}
