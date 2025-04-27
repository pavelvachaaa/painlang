// Jednoduché aritmetiky
let a: number = 5;
let b: number = 2;
let c: number = 3;

print(a + b * c); // expected 11

print((a + b) * c); // expected 21

let d: number = a * b - c;
print(d); // expected 7

let e: number = a * (b - c);
print(e); // expected -5

print(a - b * c + a); // expected 4

print((a - b) * (c + a)); // expected 24

let f: number = b * b * c;
print(f); // expected 12

let g: number = a - (b - c) * a;
print(g); // expected 10

print(a * b - a * c); // expected -5

print((a * (b - c)) * (a - b)); // expected -15

// Jednoduchá unarita
a= 5;
b= 2;
b= 7;

print(-a + b * c);
// (-5) + (2 * 7) = (-5) + 14 = 9

print(a + -b * c);
// 5 + (-2 * 7) = 5 + (-14) = -9

print(-(a + b) * c);
// -(5 + 2) * 7 = (-7) * 7 = -49

print(-a * -b + c);
// (-5) * (-2) + 7 = 10 + 7 = 17

let d: number = -(b + c) * a;
print(d);
// -(2 + 7) * 5 = (-9) * 5 = -45

let e: number = -a - b - -c;
print(e);
// (-5) - 2 - (-7) = (-5) - 2 + 7 = 0

print(a * -(b + -c));
// 5 * -(2 + (-7)) = 5 * -(2 - 7) = 5 * -(-5) = 5 * 5 = 25

let f: number = -(a * b) - (c * -b);
print(f);
// -(5 * 2) - (7 * -2)
// -10 - (-14)
// -10 + 14 = 4