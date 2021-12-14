
#include <iostream>
#include<stdio.h>
#include<cstdlib>

#define WRONG -1000

static double x1,x2,x3,x4;//运算数
static int m1,m2,m3,m4;//运算符
static int is_threeplusone;//3+1?
static int is_wrong = 0;//检验出错

double Calculate_two(double a, double b, int i);
double Calculate_three(double a, double b, double c, int i, int j, int k);
int manager(double a, double b, double c, double d);
void circulate(double* num);
void print();
char op(int i);

//两个运算数，用i表示运算符号，0123对应+-*/
//不考虑除数有零（暂且规定运算数不为零
double Calculate_two(double a, double b, int i) {
    double result = WRONG;
    if (b == 0 && i == 3) {
        is_wrong = 1;
        return WRONG;//除零返回错误
    }
    switch (i) {
    case 0:result = a + b;break;
    case 1:result = a - b;break;
    case 2:result = a * b;break;
    case 3:result = a / b;break;
    }
    return result;
}
//三个运算数，i、j对应运算符,k表示先算前两个（0）还是后两个（1）
double Calculate_three(double a, double b, double c, int i,int j,int k){
    double result = WRONG;
    double fresult = WRONG;
    if (k == 0) {
        result = Calculate_two(a, b, i);
        if (result != WRONG)  fresult = Calculate_two(result, c, j);
        else fresult = WRONG;
    }
    else if (k == 1) {
        result = Calculate_two(b, c, j);
        if (result != WRONG)  fresult = Calculate_two(a, result, i);
        else fresult = WRONG;
    }
    return fresult;
}

//如果是三个数和一个数运算，需要四个参数；如果是两个数和两个数运算，需要三个参数
//成功返回1
int manager(double a, double b, double c, double d) {
    /*对于3 + 1型，m1, m2, m3，m4对应第一个运算符，第二个运算符，第三个运算符，先算前两个还是后两个
    所以calculate_three中的ij k对应m1,m2,m4
    对于2 + 2型，m1.m2.m3分别对应第一，第二，第三个运算符*/
    double r1 = WRONG;
    double r2 = WRONG;
    double r3 = WRONG;
    for (m1 = 0;m1 < 4;m1++) {
        for (m2 = 0;m2 < 4;m2++) {
            for (m3 = 0;m3 < 4;m3++) {
                for (m4 = 0;m4 < 2;m4++) {
                    r1 = Calculate_three(x1, x2, x3, m1, m2, m4);
                    if (r1 != WRONG) {
                        r2 = Calculate_two(r1, x4, m3);
                        if (r2 == 24) {
                            is_threeplusone = 0;
 //                           printf("success in 3+1\n");
                            print();
                            return 1;
                        }
                    }
                }
            }
        }
    }
    for (m1 = 0;m1 < 4;m1++) {
        for (m2 = 0;m2 < 4;m2++) {
            for (m3 = 0;m3 < 4;m3++) {
                r1 = Calculate_two(x1, x2, m1);
                r2 = Calculate_two(x3, x4, m3);
                if (r1 != WRONG && r2 != WRONG) {
                    r3 = Calculate_two(r1, r2, m2);
                    if (r3 == 24) {
                        is_threeplusone = 1;
  //                      printf("success in 2+2\n");
                        print();
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

//轮换四个运算数
void circulate(double* num) {
    int  i, j, k, l;
    //做四个数字轮换
    for (i = 0;i < 4;i++) {
        x1 = num[i];
        for (j = 0;j < 4;j++) {
            if (j == i) continue;
            x2 = num[j];
            for (k = 0;k < 4;k++) {
                if (k == i || k == j) continue;
                x3 = num[k];
                for (l = 0;l < 4;l++) {
                    if (l == i || l == j || l == k) continue;
                    x4 = num[l];
 //                   printf("%d %d %d %d\n", x1, x2, x3, x4);
                    if (manager(x1, x2, x3, x4) == 1) return;
                }
            }
        }
    }
    printf("fail to find answer\n");
}

char op(int i) {//返回运算符
    switch (i) {
    case 0:return '+';
    case 1:return '-';
    case 2:return '*';
    case 3:return '/';
    default:return '0';
    }
}

//根据全局变量x和m输出表达式
//3+1不管先算前两个还是后两个都最多加一个括号
//2+2最多可以加两个括号
//从里到外推
void print(){
    char a, b, c;
    a = op(m1);
    b = op(m2);
    c = op(m3);
    if (is_threeplusone == 0) {//3+1
        if (m4 == 0) {//先算前两个
            if (m1 <= 1 && m2 >= 2) {
                printf("( %.0f %c %.0f )%c %.0f %c %.0f\n", x1, a, x2, b, x3, c, x4);
            }
            else if ((m1 <= 1 && m3 >= 2)||(m2 <= 1 && m3 >= 2 )) {
                printf("(%.0f %c %.0f %c %.0f )%c %.0f\n", x1, a, x2, b, x3, c, x4);
            }
            else printf("%.0f %c %.0f %c %.0f %c %.0f\n", x1, a, x2, b, x3, c, x4);
        }
        else {
            if (m1 >= 2 && m2 <= 1) {
                printf("%.0f %c( %.0f %c %.0f )%c %.0f\n", x1, a, x2, b, x3, c, x4);
            }
            else if ((m1 <= 1 && m3 >= 2)||(m2 <= 1 && m3 >= 2)) {
                printf("(%.0f %c %.0f %c %.0f )%c %.0f\n", x1, a, x2, b, x3, c, x4);
            }
            else printf("%.0f %c %.0f %c %.0f %c %.0f\n", x1, a, x2, b, x3, c, x4);
        }
    }
    else {
        if (m1 <= 1 && m3 <= 1 && m2 >= 2) {
            printf("( %.0f %c %.0f )%c( %.0f %c %.0f )\n", x1, a, x2, b, x3, c, x4);
        }
        else if (m1 <= 1 && m2 >= 2) {
            printf("(%.0f %c %.0f )%c %.0f %c %.0f\n", x1, a, x2, b, x3, c, x4);
        }
        else if (m3 <= 1 && m2 >= 2) {
            printf("%.0f %c %.0f %c( %.0f %c %.0f )\n", x1, a, x2, b, x3, c, x4);
        }
        else printf("%.0f %c %.0f %c %.0f %c %.0f\n", x1, a, x2, b, x3, c, x4);
    }
}

int main()
{
    int n,i;
    double* a;
    printf("请输入需要计算几个24点(<10)：");
    scanf_s("%d", &n);
    printf("请输入%d个运算数：\n",4*n);
    printf("------------------\n");
    a = (double*)malloc(4 * n * sizeof(double));
    for (i = 0;i < 4 * n;i++) {
        scanf_s("%lf", &a[i]);
    }
    printf("-------------------\n");
    printf("结果是：\n");
    for (i = 0;i < 4 * n;i += 4) {
        circulate(a + i);
    }
    printf("-------------------\n");
    printf("按任意键终止\n");
    getchar();
    getchar();
//    printf("%d\n", Calculate_three(1,2,2,1,1,1));
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
