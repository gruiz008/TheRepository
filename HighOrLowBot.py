import discord
import os
import random
from discord.ext import commands
from discord.ext.commands import MissingRequiredArgument
from dotenv import load_dotenv
from discord.ui import View, Button

load_dotenv()
TOKEN = os.environ['DISCORD_TOKEN']

intents = discord.Intents.default()
intents.messages = True
intents.members = True
intents.message_content = True

client = commands.Bot(command_prefix="/", intents=intents)

pre_game_messages = "Ready to roll? Select High or Low then Use /roll (number)"


@client.event
async def on_ready():
    print(f'Logged in as {client.user}')


class RollGameView(View):
    def __init__(self, ctx, timeout):
        super().__init__()
        self.ctx = ctx
        self.timeout = timeout

    @discord.ui.button(label='High')
    async def high_button(self, interaction: discord.Interaction, button: discord.ui.Button):
        await interaction.response.send_message(f"{self.ctx.author.mention} selected High.", ephemeral=False)

    @discord.ui.button(label="Low")
    async def low_button(self, interaction: discord.Interaction, button: discord.ui.Button):
        await interaction.response.send_message(f"{self.ctx.author.mention} selected Low.", ephemeral=False)


@client.command(name="HoL")
async def HoL(ctx):
    await ctx.send(pre_game_messages)

    view = RollGameView(ctx, timeout=30)
    await ctx.send(view=view)


@client.event
async def on_command_error(ctx, error):
    if isinstance(error, MissingRequiredArgument):
        results = random.randint(1, 100)
        await ctx.send(f"{ctx.author.mention} rolled: {results} (1-100)")


@client.command(name="roll")
async def roll(ctx, num_roll: int):
    if num_roll <= 0:
        await ctx.send("Why did you try to roll a negative?! Roll again")
        return
    results = random.randint(1, num_roll)
    await ctx.send(f"{ctx.author.mention} rolled: {results} (1-{num_roll})")


client.run(TOKEN)
