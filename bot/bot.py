import discord
import asyncio
import random
import json
import time
from datetime import datetime
import tzlocal

client = discord.Client()
INDEX_FILE = "/home/eddie/code/c++/message-engine/bot/index.txt"
RAW_DIR = "/home/eddie/code/c++/message-engine/raw/"
FULL_FILE = "/home/eddie/code/c++/message-engine/messages/message_full.json"

@client.event
async def on_message(message): 
    if message.author == client.user:
        return
    message.content = message.content.lower()
    if message.content.startswith("?hear"):
        person = message.content[6:].lower()
        if person == "eli":
            person = "elijah"
            f = open(RAW_DIR + person.capitalize() + ".json", mode='r', encoding='utf-8')
        elif person == "jj":
            person  = "JJJ"
            f = open(RAW_DIR + person + ".json", mode='r', encoding='utf-8')
        elif person == "jjsan":
            person = "JJ"
            f = open(RAW_DIR + person + ".json", mode='r', encoding='utf-8')
        elif person == "chris":
            person = "Christopher"
            f = open(RAW_DIR + person + ".json", mode='r', encoding='utf-8')
        else:
            if person == "sam":
                person = "samuel"
            f = open(RAW_DIR + person.capitalize() + ".json", mode='r', encoding='utf-8')
        json_data = f.read()
        parsed = json.loads(json_data)
        messages = parsed["messages"] 
        entry = messages[random.randint(0, len(messages) - 1)]

        index = entry["index_number"]

        context_file = open(INDEX_FILE, mode='w', encoding='utf-8')
        context_file.write(str(index))

        await message.channel.send(to_string(entry))
    
    if message.content.startswith("?context"):
        command = message.content.split(" ")[1]
        counter = int(message.content.split(" ")[2])
        if counter > 100:
            await message.channel.send("Too big dumbass! I knew you would try this shit JJ!")
            return
        # Grab index number -> 
        if command == "prev":
            f = open(INDEX_FILE, mode='r', encoding='utf-8')
            index = f.read()
            if index == "":
                await message.channel.send("No context to show (try using ?hear first)")
                return
            full = open(FULL_FILE, mode='r', encoding='utf-8')
            json_data = full.read()
            parsed = json.loads(json_data)
            messages = parsed["messages"] 
            entry = messages[int(index) - counter]
            if counter == 0:
                await message.channel.send("**" + to_string(entry) + "**\n---------------------------------------------------------------------------")
                return
            await message.channel.send(to_string(entry) + "\n---------------------------------------------------------------------------")
            time.sleep(1.7)
            message.content = message.content.replace(str(counter), str(counter - 1))
            await on_message(message)

        elif command == "next":
            f = open(INDEX_FILE, mode='r', encoding='utf-8')
            index = f.read()
            if index == "":
                await message.channel.send("No context to show (try using ?hear first)")
                return
            full = open(FULL_FILE, mode='r', encoding='utf-8')
            json_data = full.read()
            parsed = json.loads(json_data)
            messages = parsed["messages"] 
            entry = messages[int(index)]
            await message.channel.send("**" + to_string(entry) + "**\n---------------------------------------------------------------------------")

            for i in range(1, counter + 1):
                entry = messages[int(index) + i]
                time.sleep(1.7)
                await message.channel.send(to_string(entry) + "\n---------------------------------------------------------------------------")
            await message.channel.send("**END OF CONVERSATION**")
            context_file = open(INDEX_FILE, mode='w', encoding='utf-8')
            context_file.write(str(int(index) + int(counter)))

            return
            # message.content = message.content.replace(str(counter), str(counter - 1))
            # await on_message(message)

def to_string(entry):
    author = entry["sender_name"]
    timestamp = entry["timestamp_ms"]
    msg = entry["content"]
    local_timezone = tzlocal.get_localzone() 
    local_time = datetime.fromtimestamp((timestamp / 1000), local_timezone)
    return author + " says: \n\n" + msg + "\n\n" + "Sent: " + local_time.strftime('%m/%d/%Y %H:%M:%S')

