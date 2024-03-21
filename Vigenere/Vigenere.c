#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
int main(int argc, string argv[]){
    if(argc!=2){printf("Usage: ./vigenere keyword\n"); return 1;}
    string s=argv[1];
    int len=strlen(s);
    int i=0, j=0;
    for(j=0;j<len;j++){s[j]=tolower(s[j]);}
    char alphabet[26];
    i=0;
    for(char letter = 'a'; letter<='z'; letter++){alphabet[i]=letter; i++;}
    int key[len];
    for(i=0; i<len; i++){
        j=0;
        while(s[i]!=alphabet[j]){j++; if(j>25){printf("Usage: ./vigenere keyword\n"); return 1;} }
        if(s[i]==alphabet[j]){key[i]=j;}
        }
    string msg=get_string("plaintext: ");
    int l=strlen(msg);
    int array[l];
    for(i=0;i<l;i++){array[i]=isupper(msg[i]);} // Important array
    string same=msg;
    string cipher=same;
    for(j=0;j<l;j++){
      same[j]=tolower(msg[j]);
    }
    int x=0, y=0, z=0;
    for(x=0;x<l;x++){
        y=0;
        while(same[x]!=alphabet[y]){y++; if(y>25){cipher[x]=same[x]; goto next;}  }
        if(z>=len){z=0;}
        if(key[z]+y<26){cipher[x]=alphabet[y+key[z]];}else{
            cipher[x]=alphabet[(y+key[z])%26];
        }
        z++;
        next: i=i*1;
    }
    for(x=0;x<l;x++){if(array[x]>0){cipher[x]=toupper(cipher[x]);} }
    printf("ciphertext: %s\n", cipher);
}
