#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "redis_op.h"
#include "make_log.h"

int main()
{
   redisContext *c;

   c=rop_connectdb_nopwd("127.0.0.1","6379");
   if(c==NULL)
   {
       printf("rop_connectdb_nopwd error!");
       exit(0);
   }

   int ret=rop_string_set(c,"qihu","haotian");
    if(ret==-1)
   {
       /* LOG(REDIS_LOG_MODULE, REDIS_LOG_PROC, "[-][GMS_REDIS] rop_string_set"); */
       exit(0);
   }

    char buf[128]={0};
    ret=rop_string_get(c,"qihu",buf);

    printf("get:%s\n",buf);

}
