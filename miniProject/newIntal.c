#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 1000

typedef struct {
    int digits[MAX_DIGITS];
    int num_digits;
} Intal;

Intal intal_create(const char* str) {
    Intal result;
    result.num_digits = strlen(str);
    for (int i = 0; i < result.num_digits; i++) {
        result.digits[result.num_digits - 1 - i] = str[i] - '0';
    }
    return result;
}

void intal_print(const Intal* a) {
    for (int i = a->num_digits - 1; i >= 0; i--) {
        printf("%d", a->digits[i]);
    }
    printf("\n");
}

Intal intal_add(const Intal* a, const Intal* b) {
    Intal result;
    int carry = 0;
    int max_digits = (a->num_digits > b->num_digits) ? a->num_digits : b->num_digits;
    for (int i = 0; i < max_digits; i++) {
        int sum = carry;
        if (i < a->num_digits) {
            sum += a->digits[i];
        }
        if (i < b->num_digits) {
            sum += b->digits[i];
        }
        result.digits[i] = sum % 10;
        carry = sum / 10;
    }
    if (carry > 0) {
        result.digits[max_digits] = carry;
        result.num_digits = max_digits + 1;
    } else {
        result.num_digits = max_digits;
    }
    return result;
}

Intal intal_multiply(const Intal* a, const Intal* b) {
    Intal result;
    result.num_digits = a->num_digits + b->num_digits;
    memset(result.digits, 0, sizeof(result.digits));

    for (int i = 0; i < a->num_digits; i++) {
        int carry = 0;
        for (int j = 0; j < b->num_digits; j++) {
            int mul = a->digits[i] * b->digits[j] + result.digits[i + j] + carry;
            result.digits[i + j] = mul % 10;
            carry = mul / 10;
        }
        if (carry > 0) {
            result.digits[i + b->num_digits] += carry;
        }
    }

    // Remove leading zeros
    while (result.num_digits > 1 && result.digits[result.num_digits - 1] == 0) {
        result.num_digits--;
    }

    return result;
}

Intal intal_fibonacci(int n) {
    Intal a = intal_create("0");
    Intal b = intal_create("1");
    Intal temp;
    if (n == 0) return a;
    if (n == 1) return b;
    for (int i = 2; i <= n; i++) {
        temp = intal_add(&a, &b);
        a = b;
        b = temp;
    }
    return b;
}

Intal intal_factorial(int n) {
    Intal result = intal_create("1");
    for (int i = 2; i <= n; i++) {
        Intal multiplier = intal_create("1");
        char digit[2];
        digit[1] = '\0';
        digit[0] = i + '0';
        multiplier = intal_create(digit);
        result = intal_multiply(&result, &multiplier);
    }
    return result;
}



int main() {
    Intal a = intal_create("123456789");
    Intal b = intal_create("987654321");

    Intal sum = intal_add(&a, &b);
    printf("a + b = ");
    intal_print(&sum);

    Intal product = intal_multiply(&a, &b);
    printf("a * b = ");
    intal_print(&product);

    int n = 150;
    Intal fib = intal_fibonacci(n);
    printf("Fibonacci(%d) = ", n);
    intal_print(&fib);

    Intal factorial = intal_factorial(n);
    printf("Factorial(%d) = ", n);
    intal_print(&factorial);

    return 0;
}
