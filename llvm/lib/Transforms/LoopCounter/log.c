#include <stdio.h>
 
void BranchLogger() {
    static int total_branch_counter = 0;
    printf("now branching! total branch counter = %d", total_branch_counter);
}