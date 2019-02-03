from twilio.rest import Client


def send_sms(message, to='+16478840492'):
    account_sid = 'AC1bb7cfc1e72e68178c5f8cea68df358f'
    auth_token = '36e3b88cc4bc102c488736858aea7a1a'
    client = Client(account_sid, auth_token)

    message = client.messages.create(
        from_='+12264075193',
        body=message,
        to=to
    )

    print(message.sid)


def make_call(url='https://grahamhoyes.com/sad.xml', to='+16478840492'):
    account_sid = 'AC1bb7cfc1e72e68178c5f8cea68df358f'
    auth_token = '36e3b88cc4bc102c488736858aea7a1a'
    client = Client(account_sid, auth_token)

    call = client.calls.create(
        url=url,
        to=to,
        from_='+12264075193'
    )

    print(call.sid)
