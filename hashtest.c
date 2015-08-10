#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include "hashtable.h"

int main() {
    printf("initialize list:\n");
    list *mylist = listinit();
    printlist(mylist);
    
    printf("\nadd things:\n");
    listinsert(mylist, nodegen("key", "value"));
    listinsert(mylist, nodegen("bloop", "dingles"));
    node *testnode = nodegen("canwe", "delete?");
    listinsert(mylist, testnode);
    printlist(mylist);

    printf("\nremove things:\n");
    listremove(mylist, testnode);
    printlist(mylist);

    printf("\nsearch for things!\n");
    node *search = listsearch(mylist, "bloop", "dingles");
    listremove(mylist, search);
    printlist(mylist);


    printf("\ntwo things should hash to the same value:\n");
    unsigned char trial_text[] = "let's check that!";
    printf("going to hash: '%s'\n", trial_text);
    unsigned char trialone[SHA_DIGEST_LENGTH];
    unsigned char trialtwo[SHA_DIGEST_LENGTH];
    hash(trial_text, trialone);
    hash(trial_text, trialtwo);
    int i;
    printf("one:\n");
    for (i = 0; i < SHA_DIGEST_LENGTH; i++) {
        printf("%02x ", trialone[i]);
    }
    printf("\ntwo:\n");
    for (i = 0; i < SHA_DIGEST_LENGTH; i++) {
        printf("%02x ", trialtwo[i]);
    }

    printf("\ninitialize the hashtable:\n");
    hashtable *table;
    table = hashinit(100);

    printf("\nwe should get reasonable keys?\n");
    unsigned char keyhash[SHA_DIGEST_LENGTH];
    printf("%d ", hashindex(table, "book", keyhash));
    printf("%d ", hashindex(table, "floop", keyhash));
    printf("%d ", hashindex(table, "waddle", keyhash));
    printf("%d ", hashindex(table, "gimlet", keyhash));
    printf("%d ", hashindex(table, "tricks", keyhash));
    printf("%d ", hashindex(table, "asdfasdf", keyhash));
    printf("%d ", hashindex(table, "giggles", keyhash));
    printf("%d ", hashindex(table, "beer", keyhash));
    printf("%d ", hashindex(table, "what?", keyhash));
    printf("%d ", hashindex(table, "suuuure", keyhash));
    printf("%d ", hashindex(table, "asdf", keyhash));

    printf("\none thing should always give the same key:\n");
    printf("'books' gives %d\n", hashindex(table, "books", keyhash));
    printf("'waddles' gives %d\n", hashindex(table, "waddles", keyhash));
    printf("'books' gives %d\n", hashindex(table, "books", keyhash));
    printf("'justnow' gives %d\n", hashindex(table, "justnow", keyhash));
    printf("'waffles' gives %d\n", hashindex(table, "waffles", keyhash));
    printf("'justnow' gives %d\n", hashindex(table, "justnow", keyhash));
    printf("'waddles' gives %d\n", hashindex(table, "waddles", keyhash));
    printf("'waffles' gives %d\n", hashindex(table, "waffles", keyhash));
    printf("'ducks' gives %d\n", hashindex(table, "ducks", keyhash));
    printf("'want' gives %d\n", hashindex(table, "want", keyhash));
    printf("'ducks' gives %d\n", hashindex(table, "ducks", keyhash));
    printf("'want' gives %d\n", hashindex(table, "want", keyhash));
    // great!

    printf("\ncan we still print everything OK?\n");
    printhashtab(table);
    // works when nothing is in it!
    
    printf("\ncan we insert stuff?\n");
    inserthash(table, "foo", "bar");
    inserthash(table, "potato", "salad");
    inserthash(table, "pants", "attack");
    printhashtab(table);


}
