import discord
import asyncio
import aiohttp
import random
import json
import requests
import time
from datetime import datetime
import tzlocal

client = discord.Client()
def pull_lyrics(artist, song):
    url = 'https://api.lyrics.ovh/v1/' + artist + '/' + song
    response = requests.get(url, stream=True)
    json_data = json.loads(response.content)
    lyrics = json_data['lyrics']
    return lyrics


@client.event
async def on_message(message): 
    if message.author == client.user:
        return
    message.content = message.content.lower()

    if message.content.startswith("?hear"):
        person = message.content[6:].lower()
        if person == "eli":
            person = "elijah"
        if person == "mustang":
            await message.channel.send("vroooooooom")
            return
        if person == "jj":
            person  = "JJJ"
            f = open("/home/eddie/code/c++/message-engine/raw/" + person + ".txt", mode='r', encoding='utf-8')
        elif person == "jjsan":
            person = "JJ"
            f = open("/home/eddie/code/c++/message-engine/raw/" + person + ".txt", mode='r', encoding='utf-8')
        elif person == "chris":
            person = "Christopher"
            f = open("/home/eddie/code/c++/message-engine/raw/" + person + ".txt", mode='r', encoding='utf-8')
        else:
            if person == "sam":
                person = "samuel"
            f = open("/home/eddie/code/c++/message-engine/raw/" + person.capitalize() + ".txt", mode='r', encoding='utf-8')
        file_lines = f.readlines()
        random_msg = random.choice(file_lines)
        msg = random_msg.split("|?|?|")[0]
        timestamp = float(random_msg.split("|?|?|")[1]) / 1000
        index_number = random_msg.split("|?|?|")[2]
        context_file = open("/home/eddie/code/python/discord/index.txt", mode='w', encoding='utf-8')
        context_file.write(index_number)

        local_timezone = tzlocal.get_localzone() 
        local_time = datetime.fromtimestamp(timestamp, local_timezone)
        await message.channel.send(msg + "\n\n" + "Sent: " + local_time.strftime('%m/%d/%Y %H:%M:%S'))

    if message.content.startswith("?points"):
        person = message.author
        
client.run()
