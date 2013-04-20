/*  	Azpazeta - Sandbox strategy game
    	Copyright (C) 2013  Adrián Arroyo Calle
	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#define LOADER_CPP
#include "loader.hpp"
wxString phrases[50]={
_("The future is writed, but I've 'tipex'"),
_("If we all think alike, someone is not thinking\nSir Winston Churchill"),
_("The man who gets up, is even larger than it has fallen"),
_("The wise person does not say all what knows, and the fool does not know all what says"),
_("When the well is dry we know the worth of water\nBenjamin Franklin"),
_("An optimist sees the opportunity in every calamity, a pessimist sees a calamity in every opportunity\nSir Winston Churchill"),
_("The fate of humanity is usually that she deserves\nAlbert Einstein"),
_("The one who was free of fault that tire the first stone\nJesus of Nazaret"),
_("If it compiles, it is good, if it boots up it is perfect\nLinus Torvalds"),
_("My name is Vadrix, and I am your god.\nLetter of GOD to Azpazeta creators"),
_("An infinite number of monkeys typing into GNU emacs would never make a good program.\nLinus Torvalds"),
_("If you think your users are idiots, only idiots will use it.\nLinus Torvalds"),
_("I'd like to say that I knew this would happen, that it's all part of the plan for world domination\nLinus Torvalds"),
_("The man is the supreme being for man\nKarl Marx"),
_("The worst fight is the one which does not do .\nKarl Marx"),
_("When I know more the man more love to my dog\nAdolf Hitler"),
_("The friend must be like money, they need you before, do not know the value.\nSocrates"),
_("True wisdom is to recognize one's own ignorance.\nSocrates"),
_("Weighs the opinions, do not count them\nSocrates"),
_("I only know that I know nothing\nSocrates"),
_("What does not kill me makes me stronger\nNietzsche"),
_("Only he who contributes to the future has the right to judge the past\nNietzsche"),
_("The world is beautiful, but has a defect called man\nNietzsche"),
_("It's fine celebrate success but it is more important to heed the lessons of failure\nBill Gates"),
_("'Do not know' has become 'Do not know yet'\nBill Gates"),
_("Sometimes life gonna hit you in the head with a brick. But do not lose faith\nSteve Jobs"),
_("In every failure there is a new opportunity\nJohn D. Rockefeller"),
_("Do not be afraid to give up the good to pursue the grandiose\nJohn D. Rockefeller"),
_("In a revolution one wins or dies, if it's true\nErnesto Che Guevara"),
_("Only one absolute maximum is that there are no absolutes\nAuguste Comte"),
_("If not try great things, not make it."),
_("Dreaming of success is good, but do it better."),
_("The circulating gold because it has value, but the paper money has value because it circulates\nKarl Marx"),
_("Internet? We're not interested in that\nBill Gates"),
_("The bed is the most dangerous place in the world: die 80%% of people\nMark Twain"),
_("No aspire to be something, aspire to be somebody\nVictor Hugo"),
_("Gold is not everything. Diamonds are also\nUncle Scrooge and Minecraft players"),
_("I have some ideals, but not like I have other\nGroucho Marx"),
_("Never go on the traveled path because it leads to where others have gone\nAlexander Graham Bell"),
_("What worries me is not that you lied to me but, from now on I can no longer believe in you\nNietzsche"),
_("It failure are successful if we learn from them\nMalcom Forbes"),
_("A good politician is one who, having been purchased, it is still affordable\nSir Winston Churchill"),
_("Reviews will not be pleasant, but they are necessary\nSir Winston Churchill"),
_("One can not argue with a mathematical theorem\nStephen Hawking"),
_("How do you know if the Earth is just another planet's hell?\nAldous Huxley"),
_("Thanks, Mario .. But the Princess is in another castle\nSuper Marios Bros"),
_("Creating underworlds...\nAzpazeta State"),
_("Mammon is dead\nThe new book of Mozilla"),
_("People will remember us always\nUnknow book written by unknow people"),
_("The money is like ice cream, more is better\nFinancial Guide of Azpazeta Second Edition")};

WindowLoader::WindowLoader()
{
	srand(time(NULL));
	int ran=rand()%50;
	number_progress=1;
	message=phrases[ran];
	prg=new wxProgressDialog(_("Loading"),message,1000);
	Next();
}
void WindowLoader::Next()
{
	prg->Update(number_progress,message);
	number_progress++;
}
void WindowLoader::Finish()
{
	prg->Update(1000,message);
}

