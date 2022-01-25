# the os module helps us access environment variables
# i.e., our API keys
import os

# these modules are for querying the Hugging Face model
import json
import requests
import time

# the Discord Python API
import discord

# this is my Hugging Face profile link
API_URL = 'https://api-inference.huggingface.co/models/educhav/'

class MyClient(discord.Client):
    def __init__(self, model_name):
        super().__init__()
        self.api_endpoint = API_URL + model_name
        # retrieve the secret API token from the system environment
        huggingface_token = os.environ['HUGGINGFACE_TOKEN']
        # format the header in our request to Hugging Face
        self.request_headers = {
            'Authorization': 'Bearer {}'.format(huggingface_token)
        }

    def query(self, payload):
        """
        make request to the Hugging Face model API
        """
        data = json.dumps(payload)
        response = requests.request('POST',
                                    self.api_endpoint,
                                    headers=self.request_headers,
                                    data=data)
        ret = json.loads(response.content.decode('utf-8'))
        return ret

    async def on_ready(self):
        # print out information when the bot wakes up
        print('Logged in as')
        print(self.user.name)
        print(self.user.id)
        print('------')
        # send a request to the model without caring about the response
        # just so that the model wakes up and starts loading
        self.query({'inputs': {'text': 'Hello!'}})

    async def on_message(self, message):
        if message.author.id == self.user.id:
            return

        # isJ = str(message.author) == "J Cole Patt#6894"

        # if message.content.startswith("\\\\killall"):
        #     isJ = False
        flags = message.content[:8]

        if "&&" in flags or "++" in flags:
            flags_length = len(message.content.split(" ")[0])
            payload = {'inputs': {'text': message.content[flags_length:]}}
            async with message.channel.typing():
                response = self.query(payload)


            bot_response = response.get('generated_text', None)

            if not bot_response:
                if 'error' in response:
                    bot_response = '`Error: {}`'.format(response['error'])
                else:
                    bot_response = 'Hmm... something is not right.'

            await message.channel.send(bot_response)


def main():
    client = MyClient('Austin-DialoGPT-small')
    client.run(os.environ['AUSTIN_DISCORD_TOKEN'])

if __name__ == '__main__':
  main()
