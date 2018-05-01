#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#include <sys/times.h>

#define REPS 100

void inssort(int a[], int left, int right) {
    int x;
    for(int i = left + 1; i <= right; i++) {
        for(int j = i; j > left && a[j] < a[j - 1]; j--) {
            x = a[j - 1];
            a[j - 1] = a[j];
            a[j] = x;
        }
    }
    return;
}

void quicksort_dualpivot(int a[], int left, int right) {
    int len = right - left;
    int x;
    if(len < 17) { // insertion sort on tiny array
        for(int i = left + 1; i <= right; i++) {
            for(int j = i; j > left && a[j] < a[j - 1]; j--) {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
            }
        }
        return;
    }

    // median indexes
    int sixth = len / 6;
    int m1 = left + sixth;
    int m2 = m1 + sixth;
    int m3 = m2 + sixth;
    int m4 = m3 + sixth;
    int m5 = m4 + sixth;

    // 5-element sorting network
    if(a[m1] > a[m2]) { x = a[m1]; a[m1] = a[m2]; a[m2] = x; }
    if(a[m4] > a[m5]) { x = a[m4]; a[m4] = a[m5]; a[m5] = x; }
    if(a[m1] > a[m3]) { x = a[m1]; a[m1] = a[m3]; a[m3] = x; }
    if(a[m2] > a[m3]) { x = a[m2]; a[m2] = a[m3]; a[m3] = x; }
    if(a[m1] > a[m4]) { x = a[m1]; a[m1] = a[m4]; a[m4] = x; }
    if(a[m3] > a[m4]) { x = a[m3]; a[m3] = a[m4]; a[m4] = x; }
    if(a[m2] > a[m5]) { x = a[m2]; a[m2] = a[m5]; a[m5] = x; }
    if(a[m2] > a[m3]) { x = a[m2]; a[m2] = a[m3]; a[m3] = x; }
    if(a[m4] > a[m5]) { x = a[m4]; a[m4] = a[m5]; a[m5] = x; }

    // pivots: [ < pivot1 | pivot1 <= && <= pivot2 | > pivot2 ]
    int pivot1 = a[m2];
    int pivot2 = a[m4];
    int diffPivots = pivot1 != pivot2;

    a[m2] = a[left];
    a[m4] = a[right];
    // center part pointers
    int less  = left  + 1;
    int great = right - 1;

    // sorting
    if(diffPivots) {
        for(int k = less; k <= great; k++) {
            x = a[k];
            if(x < pivot1) {
                a[k] = a[less];
                a[less++] = x;
            } 
            else if(x > pivot2) {
                while(a[great] > pivot2 && k < great) {
                    great--;
                }
                a[k] = a[great];
                a[great--] = x;
                x = a[k];
                if(x < pivot1) {
                    a[k] = a[less];
                    a[less++] = x;
                }
            }
        }
    } else {
        for(int k = less; k <= great; k++) {
            x = a[k];
            if(x == pivot1) {
                continue;
            } 
            if(x < pivot1) {
                a[k] = a[less];
                a[less++] = x;
            }
            else {
                while(a[great] > pivot2 && k < great) {
                    great--;
                }
                a[k] = a[great];
                a[great--] = x;
                x = a[k];
                if(x < pivot1) {
                    a[k] = a[less];
                    a[less++] = x;
                }
            }
        }
    }
    // swap
    a[left] = a[less - 1];
    a[less - 1] = pivot1;
    a[right] = a[great + 1];
    a[great + 1] = pivot2;

    // left and right parts
    quicksort_dualpivot(a, left,   less - 2);
    quicksort_dualpivot(a, great + 2, right);

    // equal elements
    if(great - less > len - 13 && diffPivots) {
        for(int k = less; k <= great; k++) {
            x = a[k];
            if(x == pivot1) {
                a[k] = a[less];
                a[less++] = x;
            }
            else if(x == pivot2) {
                a[k] = a[great];
                a[great--] = x;
                x = a[k];

                if(x == pivot1) {
                    a[k] = a[less];
                    a[less++] = x;
                }
            }
        }
    }

    // center part
    if(diffPivots) {
        quicksort_dualpivot(a, less, great);
    }
}

int med3(int ar[], int a, int b, int c) {
    return ar[a] < ar[b] ?
        (ar[b] < ar[c] ? b : ar[a] < ar[c] ? c : a)
      : (ar[b] > ar[c] ? b : ar[a] > ar[c] ? c : a);
}

void quicksort_median9(int a[], int left, int right) {
    int len = right - left;
    int x;
    if(len < 17) { // insertion sort on tiny array
        for(int i = left + 1; i <= right; i++) {
            for(int j = i; j > left && a[j] < a[j - 1]; j--) {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
            }
        }
        return;
    }

    int m = left + (len/2), s;
    int pl = left, pr = right;
    if(len > 40) {
        s = (len/8);
        pl = med3(a, left, left+s, left+2*s);
        m = med3(a, m-s, m, m+s);
        pr = med3(a, right-2*s, right-s, right);
    }
    m = med3(a, pl, m, pr);

    int pv = a[m];

    int less  = left  + 1;
    int great = right - 1;

    for(int k = less; k <= great; k++) {
        x = a[k];
        if(x < pv) {
            a[k] = a[less];
            a[less++] = x;
        } 
        else if(x > pv) {
            while(a[great] > pv && k < great) {
                great--;
            }
            a[k] = a[great];
            a[great--] = x;
            x = a[k];
            if(x < pv) {
                a[k] = a[less];
                a[less++] = x;
            }
        }
    }

    // swap
    a[left] = a[less - 1];
    a[less - 1] = pv;
    a[right] = a[great + 1];
    a[great + 1] = pv;

    // left and right parts
    quicksort_median9(a, left,   less - 2);
    quicksort_median9(a, great + 2, right);
}

void quicksort_median9_random(int a[], int left, int right) {
    int len = right - left;
    int x;
    if(len < 17) { // insertion sort on tiny array
        for(int i = left + 1; i <= right; i++) {
            for(int j = i; j > left && a[j] < a[j - 1]; j--) {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
            }
        }
        return;
    }

    int m = left + (len/2) + (rand() % (len/3) - len/6);
    int pl = left + (rand() % (len/3));
    int pr = right - (rand() % (len/3));
    if(len > 40) {
        int s = rand() % (len/8) + 1;
        pl = med3(a, left, left+s, left+2*s);
        m = med3(a, m-s, m, m+s);
        pr = med3(a, right-2*s, right-s, right);
    }
    m = med3(a, pl, m, pr);

    int pv = a[m];

    int less  = left  + 1;
    int great = right - 1;

    for(int k = less; k <= great; k++) {
        x = a[k];
        if(x < pv) {
            a[k] = a[less];
            a[less++] = x;
        } 
        else if(x > pv) {
            while(a[great] > pv && k < great) {
                great--;
            }
            a[k] = a[great];
            a[great--] = x;
            x = a[k];
            if(x < pv) {
                a[k] = a[less];
                a[less++] = x;
            }
        }
    }

    // swap
    a[left] = a[less - 1];
    a[less - 1] = pv;
    a[right] = a[great + 1];
    a[great + 1] = pv;

    // left and right parts
    quicksort_median9_random(a, left,   less - 2);
    quicksort_median9_random(a, great + 2, right);
}

void quicksort_median3_random(int a[], int left, int right) {
    int len = right - left;
    int x;
    if(len < 17) { // insertion sort on tiny array
        for(int i = left + 1; i <= right; i++) {
            for(int j = i; j > left && a[j] < a[j - 1]; j--) {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
            }
        }
        return;
    }

    int m = left + (len/2) + (rand() % (len/3) - len/6);
    int pl = left + (rand() % (len/3));
    int pr = right - (rand() % (len/3));
    m = med3(a, pl, m, pr);

    int pv = a[m];

    int less  = left  + 1;
    int great = right - 1;

    for(int k = less; k <= great; k++) {
        x = a[k];
        if(x < pv) {
            a[k] = a[less];
            a[less++] = x;
        } 
        else if(x > pv) {
            while(a[great] > pv && k < great) {
                great--;
            }
            a[k] = a[great];
            a[great--] = x;
            x = a[k];
            if(x < pv) {
                a[k] = a[less];
                a[less++] = x;
            }
        }
    }

    // swap
    a[left] = a[less - 1];
    a[less - 1] = pv;
    a[right] = a[great + 1];
    a[great + 1] = pv;

    // left and right parts
    quicksort_median3_random(a, left,   less - 2);
    quicksort_median3_random(a, great + 2, right);
}

void quicksort_median3(int a[], int left, int right) {
    int len = right - left;
    int x;
    if(len < 17) { // insertion sort on tiny array
        for(int i = left + 1; i <= right; i++) {
            for(int j = i; j > left && a[j] < a[j - 1]; j--) {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
            }
        }
        return;
    }

    int m = left + (len/2);
    int pl = left, pr = right;
    m = med3(a, pl, m, pr);

    int pv = a[m];

    int less  = left  + 1;
    int great = right - 1;

    for(int k = less; k <= great; k++) {
        x = a[k];
        if(x < pv) {
            a[k] = a[less];
            a[less++] = x;
        } 
        else if(x > pv) {
            while(a[great] > pv && k < great) {
                great--;
            }
            a[k] = a[great];
            a[great--] = x;
            x = a[k];
            if(x < pv) {
                a[k] = a[less];
                a[less++] = x;
            }
        }
    }

    // swap
    a[left] = a[less - 1];
    a[less - 1] = pv;
    a[right] = a[great + 1];
    a[great + 1] = pv;

    // left and right parts
    quicksort_median3(a, left,   less - 2);
    quicksort_median3(a, great + 2, right);
}

// Sedgewick: take middle element
void quicksort_mid(int a[], int left, int right) {
    int len = right - left;
    int x;
    if(len < 17) { // insertion sort on tiny array
        for(int i = left + 1; i <= right; i++) {
            for(int j = i; j > left && a[j] < a[j - 1]; j--) {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
            }
        }
        return;
    }

    int pv = a[left + len / 2];

    int less  = left  + 1;
    int great = right - 1;

    for(int k = less; k <= great; k++) {
        x = a[k];
        if(x < pv) {
            a[k] = a[less];
            a[less++] = x;
        } 
        else if(x > pv) {
            while(a[great] > pv && k < great) {
                great--;
            }
            a[k] = a[great];
            a[great--] = x;
            x = a[k];
            if(x < pv) {
                a[k] = a[less];
                a[less++] = x;
            }
        }
    }

    // swap
    a[left] = a[less - 1];
    a[less - 1] = pv;
    a[right] = a[great + 1];
    a[great + 1] = pv;

    // left and right parts
    quicksort_mid(a, left,   less - 2);
    quicksort_mid(a, great + 2, right);
}

void quicksort_first(int a[], int left, int right) {
    int len = right - left;
    int x;
    if(len < 17) { // insertion sort on tiny array
        for(int i = left + 1; i <= right; i++) {
            for(int j = i; j > left && a[j] < a[j - 1]; j--) {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
            }
        }
        return;
    }

    int pv = a[left];

    int less  = left  + 1;
    int great = right - 1;

    for(int k = less; k <= great; k++) {
        x = a[k];
        if(x < pv) {
            a[k] = a[less];
            a[less++] = x;
        } 
        else if(x > pv) {
            while(a[great] > pv && k < great) {
                great--;
            }
            a[k] = a[great];
            a[great--] = x;
            x = a[k];
            if(x < pv) {
                a[k] = a[less];
                a[less++] = x;
            }
        }
    }

    // swap
    a[left] = a[less - 1];
    a[less - 1] = pv;
    a[right] = a[great + 1];
    a[great + 1] = pv;

    // left and right parts
    quicksort_first(a, left,   less - 2);
    quicksort_first(a, great + 2, right);
}

void quicksort_random(int a[], int left, int right) {
    int len = right - left;
    int x;
    if(len < 17) { // insertion sort on tiny array
        for(int i = left + 1; i <= right; i++) {
            for(int j = i; j > left && a[j] < a[j - 1]; j--) {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
            }
        }
        return;
    }

    int pv = a[(rand() % (right - left + 1)) + left];

    int less  = left  + 1;
    int great = right - 1;

    for(int k = less; k <= great; k++) {
        x = a[k];
        if(x < pv) {
            a[k] = a[less];
            a[less++] = x;
        } 
        else if(x > pv) {
            while(a[great] > pv && k < great) {
                great--;
            }
            a[k] = a[great];
            a[great--] = x;
            x = a[k];
            if(x < pv) {
                a[k] = a[less];
                a[less++] = x;
            }
        }
    }

    // swap
    a[left] = a[less - 1];
    a[less - 1] = pv;
    a[right] = a[great + 1];
    a[great + 1] = pv;

    // left and right parts
    quicksort_random(a, left,   less - 2);
    quicksort_random(a, great + 2, right);
}

int main(int argc, char* argv[]) {
    srand(0);

    if(argc < 2) {
        fprintf(stderr, "Give file to read as argument.\n");
        return EXIT_FAILURE;
    }

    printf("algorithm,instance,time\n");

    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL) {
        fprintf(stderr, "File cannot be opened.\n");
        return EXIT_FAILURE;
    }

    char *line = NULL;
    int lineno = 0;
    size_t len = 0;
    ssize_t read;

    while((read = getline(&line, &len, fp)) != -1) {
        lineno++;
        int length = 0;
        int size = 1000;
        int *a = calloc(size, sizeof(int));


        char *ptr = NULL;
        char *token = strtok_r(line, ",", &ptr);
        while(token != NULL) {
            a[length++] = atoi(token);
            if(length == size) {
                size *= 2;
                a = realloc(a, size * sizeof(int));
            }
            token = strtok_r(NULL, ",", &ptr);
        }
        a = realloc(a, (length + 1) * sizeof(int));
        a[length] = INT_MAX;

        int *b = calloc(length + 1, sizeof(int));

#ifdef DEBUG
        printf("length: %d\n", length);
        for(int i = 0; i <= length; i++) {
            printf("%d, ", a[i]);
        }
        printf("\n");
#endif

        if(length > 0) {
            struct tms t, tt;
            int timval;

            times(&t);
            for(int i = 0; i < REPS; i++) {
                memcpy(b, a, length + 1);
                inssort(b, 0, length - 1);
            }
            times(&tt);
            timval = (tt.tms_utime - t.tms_utime) + (tt.tms_stime - t.tms_stime);
            printf("insertion,%d,%i\n", lineno, timval);

            times(&t);
            for(int i = 0; i < REPS; i++) {
                memcpy(b, a, length + 1);
                quicksort_first(b, 0, length - 1);
            }
            times(&tt);
            timval = (tt.tms_utime - t.tms_utime) + (tt.tms_stime - t.tms_stime);
            printf("first,%d,%i\n", lineno, timval);

            times(&t);
            for(int i = 0; i < REPS; i++) {
                memcpy(b, a, length + 1);
                quicksort_random(b, 0, length - 1);
            }
            times(&tt);
            timval = (tt.tms_utime - t.tms_utime) + (tt.tms_stime - t.tms_stime);
            printf("random,%d,%i\n", lineno, timval);

            times(&t);
            for(int i = 0; i < REPS; i++) {
                memcpy(b, a, length + 1);
                quicksort_mid(b, 0, length - 1);
            }
            times(&tt);
            timval = (tt.tms_utime - t.tms_utime) + (tt.tms_stime - t.tms_stime);
            printf("mid,%d,%i\n", lineno, timval);

            times(&t);
            for(int i = 0; i < REPS; i++) {
                memcpy(b, a, length + 1);
                quicksort_median3(b, 0, length - 1);
            }
            times(&tt);
            timval = (tt.tms_utime - t.tms_utime) + (tt.tms_stime - t.tms_stime);
            printf("median 3,%d,%i\n", lineno, timval);

            times(&t);
            for(int i = 0; i < REPS; i++) {
                memcpy(b, a, length + 1);
                quicksort_median3_random(b, 0, length - 1);
            }
            times(&tt);
            timval = (tt.tms_utime - t.tms_utime) + (tt.tms_stime - t.tms_stime);
            printf("median 3 random,%d,%i\n", lineno, timval);

            times(&t);
            for(int i = 0; i < REPS; i++) {
                memcpy(b, a, length + 1);
                quicksort_median9(b, 0, length - 1);
            }
            times(&tt);
            timval = (tt.tms_utime - t.tms_utime) + (tt.tms_stime - t.tms_stime);
            printf("median 9,%d,%i\n", lineno, timval);

            times(&t);
            for(int i = 0; i < REPS; i++) {
                memcpy(b, a, length + 1);
                quicksort_median9_random(b, 0, length - 1);
            }
            times(&tt);
            timval = (tt.tms_utime - t.tms_utime) + (tt.tms_stime - t.tms_stime);
            printf("median 9 random,%d,%i\n", lineno, timval);

            times(&t);
            for(int i = 0; i < REPS; i++) {
                memcpy(b, a, length + 1);
                quicksort_dualpivot(b, 0, length - 1);
            }
            times(&tt);
            timval = (tt.tms_utime - t.tms_utime) + (tt.tms_stime - t.tms_stime);
            printf("dual pivot,%d,%i\n", lineno, timval);

#ifdef DEBUG
            for(int i = 0; i < length; i++) {
                printf("%d, ", b[i]);
            }
            printf("\n");
            for(int i = 1; i < length; i++) {
                if(b[i] < b[i-1]) {
                    fprintf(stderr, "Failed to sort line %d: %d before %d!\n", lineno, b[i-1], b[i]);
                    return EXIT_FAILURE;
                }
            }
#endif
        }

        free(a);
        free(b);
    }

    fclose(fp);
    if(line) {
        free(line);
    }

    return EXIT_SUCCESS;
}
