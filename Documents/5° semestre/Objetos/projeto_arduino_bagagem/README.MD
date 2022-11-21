# Rastreador de bagagens em tempo real: um exemplo utilizando Arduino e Internet das Coisas

## Abstract. This work proposes a device to track back luggages using Arduino as hardware, sending data through internet of things frameworks and viewing results in a mobile application__

<br>

## Resumo. Este trabalho propõe a utilização de um dispositivo para rastreamento de bagagens utilizando Arduino como hardware e envio de dados através de Internet das coisas e disponibilização visual em um aplicativo para celular

<br>

## Contido neste projeto: 

1. arduino.ino: Programa escrito em arduino responsável pela emissão de mensagens MQTT a um broker de messageria.

2. exemplo_mensagem.json: exemplo de mensagem enviada pelo programa arduino.

3. cria_banco_dados.py: script de criação de tabela dynamdob

4. aplicacao_consumidora: AWS lambda em python responsável pela leitura das mensagens e gravação no banco de dados.



