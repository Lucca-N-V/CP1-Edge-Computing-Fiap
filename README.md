# CP1-Edge-Computing-Fiap

Projeto de um detector de luminosidade para a **Vinheria Agnello**, desenvolvido como parte do **CP1 da FIAP**.

## Descrição do projeto

O projeto envolvia o uso do Atmega 328P para capturar e informar a porcentagem luminosa no armazém de vinhos, visto que os vinhos quando expostos a luz podem sofrer alterações nos compostos organicos.

## Materiais utilizados

Para a criação deste aparelho, utilizamos os seguintes materiais:

* 1 Arduino Uno
* 1 LDR
* 1 Buzzer
* 1 LCD 16x2 I2C
* 1 LED vermelho
* 1 LED amarelo
* 1 LED verde
* 3 resistores de 1k ohm
* 17 fios

#Tecnologias utilizadas

Para a criação deste aparelho, utilizamos as seguintes tecnologias:

* C++
* Wokwi
* Tinkercad
* Arduino IDE
* 
## Como funciona

O aparelho fica no escuro onde constantemente mede a quantidade luminosa pelo LDR. Caso a iluminação chegue em níveis próximos a inadequados o LED amarelo acendera e o buzzer tocara até a porcentagem luminosa mudar. Caso o nível de luz ficar nos parâmetros inaceitáveis somente o LED vermelho acenderá até alguma mudança, e se os níveis estiverem dentro do padrão somente o LED verde acenderá até alguma mudança.  

## Como usar

O aparelho deverá ficar dentro de um quarto, prioritariamente escuro, e te informara, por meio dos LEDS buzzer e LCD, a porcentagem luminosa do quarto em questão, sendo assim um sensor luminoso focado no escuro, te alertando caso os níveis de iluminação estiverem alto.

## Autores
Leandro Rodrigues Barbosa

Eduardo Miranda Mororo

Lucca Neufeld Vecchiatti

Victor krause Esteves

Henrique Nascimento
