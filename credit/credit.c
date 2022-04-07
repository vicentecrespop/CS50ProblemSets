#include <cs50.h>
#include <stdio.h>
#include <math.h>

void checarCartao(int digito, int primeiros);

int main(void)
{
    int valorUltimo = 0;
    int digitos = 0;
    int valorPenultimo = 0;
    int somaPrimeira = 0;
    int somaSegunda = 0;
    long card = get_long("Number: ");
    long cartaoNovo = card;
    do
    {
        valorUltimo = cartaoNovo % 10;
        cartaoNovo = (cartaoNovo - valorUltimo) / 10;
        if (cartaoNovo == 0)
        {
            digitos++;
        }
        else
        {
            digitos += 2;
        }
        valorPenultimo = cartaoNovo % 10;
        cartaoNovo = (cartaoNovo - valorPenultimo) / 10;

        if (valorPenultimo >= 5)
        {
            int dobro = valorPenultimo * 2;
            valorPenultimo = dobro % 10;
            dobro = (dobro - valorPenultimo) / 10;
            valorPenultimo += dobro;
        }
        else
        {
            valorPenultimo = valorPenultimo * 2;
        }
        somaSegunda += valorUltimo;
        somaPrimeira += valorPenultimo;
    }
    while (cartaoNovo > 0);

    somaPrimeira += somaSegunda;
    card = card / pow(10, digitos - 2);
    int primeirosDigitos = card;

    //Checks the Luhn's algorithm and if it's valid then it calls the function checarCartao and if not it prints "INVALID" in the screen
    if (somaPrimeira % 10 == 0)
    {
        checarCartao(digitos, primeirosDigitos);
    }
    else
    {
        printf("INVALID\n");
    }
}



//Function that receives the number os digits tha card has and the two first digits and prints the name of the card or "INVALID" if not a valid card
void checarCartao(int digito, int primeiros)
{
    if (digito == 15 && (primeiros == 34 || primeiros == 37))
    {
        printf("AMEX\n");
    }
    else if (digito == 16 && (primeiros >= 51 && primeiros <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((digito == 13 || digito == 16) && primeiros >= 40 && primeiros <= 49)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}