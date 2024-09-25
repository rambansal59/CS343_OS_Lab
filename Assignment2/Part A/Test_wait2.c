#include "types.h"
#include "stat.h"
#include "user.h"
int sum_of_digits(int n){
  int ans=0;
  while(n){
    ans += n%10;
    n/=10;
  }
  return ans;
}

int main(int argc, char *argv[]){
  int stime, retime, rutime;
  fork();
  // fork();
  if(fork() == 0){
    // This is Child process
    int num;
    char buf[32]; // Buffer to hold the input string
    printf(1, "Enter a positive integer: ");
    // Reading input from keyboard
    read(0, buf, sizeof(buf));

	for(int i=0; i<1420; i++){
		printf(1,".");
	}
	
    // Convert the input string to an integer
    num = atoi(buf);
    // Compute sum of digits of num
    
    int result = sum_of_digits(num);
    
    // Print the result
    printf(1, "\nsum of the digits of %d is %d\n", num, result);
    exit();
  }
  else {
    // This is Parent process
    
    wait2(&stime, &retime, &rutime);
    printf(1, "stime: %d, retime: %d, rutime: %d\n", stime, retime, rutime);
  }
  exit();
}

