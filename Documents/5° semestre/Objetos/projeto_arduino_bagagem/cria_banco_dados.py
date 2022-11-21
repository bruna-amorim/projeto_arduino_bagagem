##
import boto3

dynamodb = boto3.client('dynamodb')

response = dynamodb.create_table(
    TableName='PosicaoBagagemDB',
    KeySchema=[
        {'AttributeName': 'Id', 'KeyType': 'HASH'},  # Partition key
        {'AttributeName': 'Timestamp', 'KeyType': 'RANGE'}  # Sort key
    ],
    AttributeDefinitions=[
        {'AttributeName': 'Id', 'AttributeType': 'S'},
        {'AttributeName': 'Timestamp', 'AttributeType': 'S'}
    ],
    BillingMode='PAY_PER_REQUEST'
)