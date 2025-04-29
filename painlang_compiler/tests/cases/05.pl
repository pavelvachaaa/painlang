include "stdlib/math"


let x: number= 0; // todo: bug když není init, tak ve for loopu segfaultí?!
for (let r : number = 0; r < 10; r++) {
    x = pow(2, r);
    print(x);
}

let res: number = modulo(3,base);
print("Modulo test:");
print(res);


print("isEven test:");
let resVen: bool = isEven(1);
print(resVen);

resVen = isEven(44);
print(resVen);

resVen = isEven(43);
print(resVen);

print("isOdd test:");
let resVen: bool = isOdd(1);
print(resVen);

print("isPrime");
let primeTest:number = isPrime(13);
print(primeTest);



let primeTest2:number = isPrime(10);
print(primeTest2);
