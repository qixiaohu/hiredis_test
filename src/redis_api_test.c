#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <hiredis.h>

int main()
{
    redisContext *c;
    redisReply *reply;

    c = redisConnect("127.0.0.1", 6379);
    if (c == NULL || c->err) 
    {
        if (c)
        {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        }
        else
        {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }

    reply=redisCommand(c,"set %s %s","itcast","nihao");
    if(reply==NULL)
    {
        perror("redisCommand error");
        exit(0);
    }
    printf("set success!\n");
    freeReplyObject(reply);

    reply=redisCommand(c,"get %s","itcast");
    if(reply==NULL)
    {
        printf("redisCommand error");
        exit(0);
    }
    printf("get:%s\n",reply->str);
    freeReplyObject(reply);
    
    reply=redisCommand(c,"LPUSH %s %s","qihuwei","qihaotian");
    if(reply==NULL)
    {
        printf("redisCommand error");
        exit(0);
    }
    freeReplyObject(reply);

    reply=redisCommand(c,"LRANGE %s 0 -1","qihuwei");
    if(reply==NULL)
    {
        printf("redisCommand error");
        exit(0);
    }

    printf("elements:%d\n",(int)reply->elements);
    for(int i=0;i<reply->elements;i++)
    {
        printf("[%d]:%s\n",i,reply->element[i]->str);
    }
    freeReplyObject(reply);



    return 0;
}
