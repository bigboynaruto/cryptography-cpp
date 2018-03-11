#include <iostream>
#include <iomanip>

#include "Long.h"

void arithmetics();
void mobius();
void euler();
void legendre();
void jacobi();
void primality_test();
void factorization();
void dlog();
void crypto();
void diffie_hellman();

int main() {
    Random::seed(time(NULL));
    string opt;
    do {
        cout << "1. Arithmetics" << endl
            << "2. Mobius function" << endl
            << "3. Euler totient function" << endl
            << "4. Legendre symbol" << endl
            << "5. Jacobi symbol" << endl
            << "6. Primality test" << endl
            << "7. Factorization" << endl
            << "8. Discrete logarithm" << endl
            << "9. Cryptography" << endl
            << "d. Diffie-Hellman" << endl
            << "*. Exit" << endl
            << "=========================" << endl
            << "> ";
        getline(cin, opt);

        switch (opt[0]) {
            case '1':
                arithmetics();
                break;
            case '2':
                mobius();
                break;
            case '3':
                euler();
                break;
            case '4':
                legendre();
                break;
            case '5':
                jacobi();
                break;
            case '6':
                primality_test();
                break;
            case '7':
                factorization();
                break;
            case '8':
                dlog();
                break;
            case '9':
                crypto();
                break;
            case 'd':
                diffie_hellman();
                break;
            default:
                opt = "q";
        }
        cout << endl;
    } while (cin && opt != "q");
}

void arithmetics() {
    string s1, s2;

    cout << "n1> ";
    getline(cin, s1);
    cout << "n2> ";
    getline(cin, s2);

    Long n1(s1), n2(s2);
    cout << "n1 = " << n1 << ", n2 = " << n2 << endl;
    cout << n1 << " + " << n2 << " = " << n1 + n2 << endl;
    cout << n1 << " - " << n2 << " = " << n1 - n2 << endl;
    cout << n1 << " * " << n2 << " = " << n1 * n2 << endl;
    try {
        cout << n1 << " / " << n2 << " = " << n1 / n2 << endl;
        cout << n1 << " % " << n2 << " = " << n1 % n2 << endl;
    }
    catch (LongException e) {
        cout << "ERROR: " << e.what() << endl;
    }

    cout << "pow (y for yes)> ";
    getline(cin, s1);
    if (s1 == "y" || s1 == "Y")
        cout << n1 << "^" << n2 << " = " << (n1^n2) << endl;

    cout << "powmod (y for yes)> ";
    getline(cin, s1);
    if (s1 == "y" || s1 == "Y") {
        string sp;
        cout << "p> ";
        getline(cin, sp);
        Long p(sp);
        cout << "p = " << p << endl;
        cout << n1 << "^" << n2 << " = " << n1.powmod(n2, p) << " (mod " << p << ")"<< endl;
    }

    cout << "gcd (y for yes)> ";
    getline(cin, s1);
    if (s1 == "y" || s1 == "Y") {
        try {
            Long x, y;
            Long d = Long::gcd(n1, n2, x, y);
            cout << "gcd(" << n1 << ", " << n2 << ") = " << d << endl;
            cout << n1 << " * " << x << " + " << n2 << " * " << y << " = " << n1*x+n2*y << endl;
        }
        catch (LongException e) {
            cout << "ERROR: " << e.what() << endl;
        }
    }

    cout << "lcm (y for yes)> ";
    getline(cin, s1);
    if (s1 == "y" || s1 == "Y") {
        try {
            cout << "lcm(" << n1 << ", " << n2 << ") = " << Long::lcm(n1, n2) << endl;
        }
        catch (LongException e) {
            cout << "ERROR: " << e.what() << endl;
        }
    }
}

void mobius() {
    string s;
    cout << "n> ";
    getline(cin, s);

    Long n(s);
    cout << "n = " << n << endl;
    try {
        cout << "m(n) = " << Long::mobius(n) << endl;
    }
    catch (LongException e) {
        cout << "ERROR: " << e.what() << endl;
    }
}

void euler() {
    string s;
    cout << "n> ";
    getline(cin, s);

    Long n(s);
    cout << "n = " << n << endl;
    try {
        cout << "Ф(n) = " << Long::euler(n) << endl;
    }
    catch (LongException e) {
        cout << "ERROR: " << e.what() << endl;
    }
}

void legendre() {
    string sa, sb;
    cout << "a> ";
    getline(cin, sa);
    cout << "b> ";
    getline(cin, sb);

    Long a(sa), b(sb);
    cout << "a = " << a << ", b = " << b << endl;
    try {
        cout << "(a/b) = " << Long::legendre_sym(a, b) << endl;
    }
    catch (LongException e) {
        cout << "ERROR: " << e.what() << endl;
    }
}

void jacobi() {
    string sa, sb;
    cout << "a> ";
    getline(cin, sa);
    cout << "b> ";
    getline(cin, sb);

    Long a(sa), b(sb);
    cout << "a = " << a << ", b = " << b << endl;
    try {
        cout << "(a/b) = " << Long::jacobi_sym(a, b) << endl;
    }
    catch (LongException e) {
        cout << "ERROR: " << e.what() << endl;
    }
}

void primality_test() {
    string s;
    cout << "n> ";
    getline(cin, s);

    Long n(s);
    cout << "n = " << n << endl;

    string opt;
    cout << "1. Pratt's certificate" << endl
        << "2. Miller-Rabin test" << endl
        << "3. Solovay-Strassen test" << endl
        << "> ";
    getline(cin, opt);

    if (opt[0] == '1') {
        if (n.lucas_test(n.log2()))
            cout << n << " is not prime";
        else cout << n << " is prime" << endl;
    }
    else if (opt[0] == '2') {
        if (n.miller_rabin_test(20))
            cout << n << " is not prime";
        else cout << n << " is probably prime" << endl;
    }
    else if (opt[0] == '3') {
        if (n.solovay_strassen_test(n.log2()))
            cout << n << " is not prime";
        else cout << n << " is probably prime" << endl;
    }
    else {
        cout << "ERROR: Invalid option." << endl;
    }
}

void factorization() {
    string s;
    cout << "n> ";
    getline(cin, s);

    Long n(s);
    cout << "n = " << n << endl;

    cout << "FACTORS: ";
    auto factors = n.rho_pollard_factorization();
    for (Long l : factors) {
        cout << l << " ";
    }
    cout << endl;
}

void dlog() {
    string sa, sb, sp;
    cout << "a^x = b (mod p), a - generator of Zp, b є Zp" << endl;
    cout << "a = ";
    getline(cin, sa);
    cout << "b = ";
    getline(cin, sb);
    cout << "p = ";
    getline(cin, sp);

    Long a(sa), b(sb), p(sp);
    try {
        Long x = a.rho_pollard_logarithm(b, p);
        if (x.is_negative()) {
            cout << "NO SOLUTION WAS FOUND!" << endl;
            return;
        }

        cout << "x = " << x << endl;
        cout << "b (mod p) = " << b % p << endl;
        cout << "a^x (mod p) = " << a.powmod(x, p) << endl;
    } catch (LongException e) {
        cout << "ERROR: " << e.what() << endl;
    }
}

void crypto() {
    string sm;
    cout << "m> ";
    getline(cin, sm);

    Long m(sm);
    cout << "m = " << m << endl;

    string opt;
    cout << "1. RSA" << endl
        << "2. ElGamal" << endl
        << "3. Elliptic curves" << endl
        << "> ";
    getline(cin, opt);

    if (opt[0] == '1') {
        RSA rsa;

        Long c = rsa.encrypt(m);
        cout << "ENCRYPT " << m << "... " << c << endl;
        Long _m = rsa.decrypt(c);
        cout << "DECRYPT " << c << "... " << _m << endl;
    }
    else if (opt[0] == '2') {
        ElGamal eg;

        auto c = eg.encrypt(m);
        cout << "ENCRYPT " << m << "... " << c.first << " " << c.second << endl;
        Long _m = eg.decrypt(c);
        cout << "DECRYPT " << c.first << " " << c.second << "... " << _m << endl;
    }
    else if (opt[0] == '3') {
        EC ec;
        auto c = ec.encrypt(m);
        cout << "ENCRYPT " << m << "... " <<  c.first << " " << c.second << endl;
        auto _m = ec.decrypt(c.first, c.second);
        cout << "DECRYPT " << c.first << " " << c.second << "... " << _m << endl;
    }
    else {
        cout << "ERROR: Invalid option." << endl;
    }
}

void diffie_hellman() {
    
    cout << "Generating prime P... " << flush;
    Long P = Random::next_prime(2);//23;
    cout << "Done." << flush << endl;

    cout << "Finding a primitive root for " << P << "... " << flush;
    Long G = Long::primitive_root(P);//9;
    cout << "Done." << flush << endl;

    cout << "P = " << P << ", G = " << G << endl;

    string line;
    cout << "Alice's private key> ";
    getline(cin, line);
    Long a(line), x = G.powmod(a, P);
    cout << "Alice's public key: " << x << endl;

    cout << "Bob's private key> ";
    getline(cin, line);
    Long b(line), y = G.powmod(b, P);
    cout << "Bob's public key: " << y << endl;
    
    Long ka = y.powmod(a, P), kb = x.powmod(b, P);
    cout << "Symmetric keys: " << ka << " and " << kb << endl;
}
