##
import boto3
import json 

dynamodb = boto3.client('dynamodb')


def handler_message(event, context):
    messagens = event['Records']
    

    for mensagem in messagens:
        body = mensagem['body']
        dados = json.loads(body)['dados']

        dynamodb.put_item(
            TableName='PosicaoBagagemDB',
            Item={
                'Id': {'S': dados['id_bagagem']},
                'Timestamp': {'S': dados['data_hora_mensagem']},
                'Latitude': {'N': str(dados['latitude'])},
                'Longitude': {'N': str(dados['longitude'])}
            }
        )

    print("Mensagens recebidas com sucesso!")

    return {
        "statusCode": 200,
        "headers": {
            "Content-Type": "application/json"
        },
        "body": json.dumps({
            "Mensagem": "Mensagens recebidas com sucesso!"
        })
    }

