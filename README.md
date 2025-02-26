# PainLang
Projekt pro splnění zápočtu na předmět NTI/PRK 2024

## Cvičení 01 

### PainLang
`prescribe [a-zA-z]+` - identifikátor (nesmí obsahovat číslo)

`-*[0-9]+` - decimální číslo

`0b[0-1]+` binární číslo

`0x[0-9a-f]` - hexadecimální číslo

Operátory:
`+,-, *, /, //, %, ^, !, %, |, <<, >>, =, ==, &,`

Keywordy:
Povinně začínají velkým písmenem

Diagnose (if),Else, Treat (arg(for loop), Prescription (), Triage (switch statement), Report (print)

Ostatní:
`(, ), {,}`

`[PL` - začátek komentáře

`PL]` - konec komentáře

`;` - středník

`->` (používá se v triage)

`dead` (místo default v healu)

Funkčnost OK:
```bash
prescribe brufen = 3;
prescribe notBrufen = 0b1001;
prescribe ventolin = (3+(3+brufen));

Diagnose(brufen == notBrufen) {
    Treat(prescribe j = 0; j <= notBrufen; j = j + 1) { 
        ventolin = brufen + brufen;
        Report(brufen);
    }
} 

Triage (ventolin) {
    4 -> Report(2);
    3 -> Report(1);
    dead -> Report(0);
}

Prescription stayHome() {
    Report(0b123)
}
```

FUNKČNOST NOT OK: (bude doplněno)

prescribe 1bruf = 2 // nesmí obsahovat číslo a ještě musí obsahovat středník


## Cvičení 02 


### Integer + rozšiřování

Neoptimalni
```ebnf
integer = '0' | n_cislice;
n_cislice =  ('1' | '2' | '3'  | '4'  | '5'  | '6'  | '7'  | '8' |  '9'), {cislice};
cislice = '0', {cislice} | n_cislice;
```

Optimální
```
integer = '0' | n_cislice;
n_cislice =  ('1' | '2' | '3'  | '4'  | '5'  | '6'  | '7'  | '8' |  '9'), {cislice};
cislice = ('0' | '1' | '2' | '3'  | '4'  | '5'  | '6'  | '7'  | '8' |  '9') ;
``` 

Desetinné čísla

```
cislo =  operator, double | double | '0';
operator = '+' | '-';
double = '0', '.', {cislice} | n_cislice | n_cislice, '.' , {cislice};
n_cislice =   ('1' | '2' | '3'  | '4'  | '5'  | '6'  | '7'  | '8' |  '9'), 
{cislice};
operator = ('-' | '+');
cislice = ('0' | '1' | '2' | '3'  | '4'  | '5'  | '6'  | '7'  | '8' |  '9') ;
```

## Cvičení 03

Ve složce `cv03`.


## Ostatní
```

<PainLang> ::= <block> | <declarations> <block>
<declarations> ::= <declaration> | <declaration> <declarations>
<declaration> ::= <var_declaration> | <fun_declaration>

```