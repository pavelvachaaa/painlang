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
let a1: number = 5;
let b1 : number= 2;
let c1:  number = 7;

print(-a1 + b1 * c1);

print(a1 + -b1* c1);


print(!false);
print(false && false);
print(false || true);
print(!(true && false));

let z : number= 3;
print(z)
z++;
print(z);


// Syntax sugar test

let pavel : number = 3;
pavel += 5;
print(pavel);