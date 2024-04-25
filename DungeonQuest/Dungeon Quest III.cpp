//Dungeon Quest III: Torn Dreams
//James Montemagno & Jason Saupp�
//Date Started: January 31st 2005 
//Date Finished: May 26th 2005
//Copyright 2005 PM Media, Code Warriors, James Montemagno, Jason Saupp�; All rights Reserved.
#include <iostream>
using namespace std;
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "header.h"
 
world map;		


int j, l, z;
//Input Variables
int dungeonchoice, choice, dungeonnum, battleoption, itemchoice, target, spellchoice, runindicator;

//Game Variables
int x, enemycount, eremain, cremain, counter, spellnum, damage, turn, gainedxp, gainedgold;
int tempsequence, tempspeedcalc;	
int sequence[7], speedcalc[7];

//Spells
//1 = Heal I		2 = Light I			3 = DFPUP I			4 = Resurrect I		5 = Fire I			6 = Ice I		7 = ATPUP I			8 = Black Hole I
//9 = Heal II		10= Light II		11= DFPUP II		12= Resurrect II	13= Fire II			14= Ice II		15= ATPUP II		16= Black Hole II
//17= Heal III		18= Light III		19= DFPUP III		20= Resurrect III	21= Fire III		22= Ice III		23= ATPUP III		24= Black Hole III
char spellname[25][21] = {" ", "Heal I" , "Light I", "DFPUP I", "Resurrect I", "Fire I", "Ice I", "ATPUP I", "Black Hole I", "Heal II", "Light II", "DFPUP II", "Resurrect II", "Fire II", "Ice II", "ATPUP II", "Black Hole II", "Heal III", "Light III", "DFPUP III", "Resurrect III", "Fire III", "Ice III", "ATPUP III", "Black Hole III"};



//Weapons
//1 = Long Sword		2 = Great Sword		3 = Excalibur
//4 = Warhammer			5 = Earth Axe		6 = Wind Spear
//7 = Mace				8 = Morning Star	9 = Skull Crusher
//10= Brass Knuckles	11= Nunchaku		12= Gloves of War
//13= Short Sword		14= Lightning Sword	15= Masamune
//16= Dagger			17= Quarter Staff	18= Death Scythe
char weaponname[19][21] = {"Unarmed", "Long Sword", "Great Sword", "Excalibur", "Warhammer", "Earth Axe", "Wind Spear", "Mace", "Morning Star", "Skull Crusher", "Brass Knuckles", "Nunchaku", "Gloves of War", "Short Sword", "Lightning Saber", "Masamune", "Dagger", "Quarter Staff", "Death Scythe"};

//Armor
//1 = Steel Plate		2 = Full Plate Mail	3 = Adamantium Armor
//4 = Raw Hide Suit		5 = Hard Leather	6 = Dragonscale Armor
//7 = Chain Mail		8 = Silver Mail		9 = Platinum Armor
//10= Trainer's Suit	11= Ancient Robe	12= Minazuki
//13= Leather Armor		14= Studded Leather	15= Armor of Shadows
//16= Mage's Robe		17= Elder's Cloak	18= Mythril Mesh
char armorname[19][21] = {"Unarmored", "Steel Plate", "Full Plate Mail", "Adamantium Armor", "Raw Hide Suit", "Hard Leather", "Dragonscale Armor", "Chain Mail", "Silver Mail", "Platinum Armor", "Trainer's Suit", "Ancient Robe", "Minazuki", "Leather Armor", "Studded Leather", "Armor of Shadows", "Mage's Robe", "Elder's Cloak", "Mythril Mesh"};

// bc = Base Class
int bchp[19], bcatp[19], bcdfp[19], bcmap[19], bcmatp[19], bcmdfp[19], bcspd[19];

//Items
//1 = Healing Potion	2 = Extra Healing Potion	3 = Elixir of Healing
//4 = Ether Potion		5 = Extra Ether Potion		6 = Resurrection Vial

////random ints
int maleorfemale[4], charclass[4], charcorrect, one, progress[7], key[7], itemnum[7], atpduration[4], dfpduration[4], guardduration[4], atpplus[4], guardplus[4], dfpplus[4];
long int gold;
float townpick, neworload, shoppike;
char gender[3][21]={"","Male","Female"};

// uc = User Character
int hp[4], uchpmax[4], ucmpmax[4], ucatp[4], ucdfp[4], mp[4], ucmatp[4], uedfp[4], uematp[4], uemdfp[4] , ueatp[4], ucmdfp[4], ucspd[4], xp[4], reqxp[4], level[4], charnum[4], weapon[4], armor[4];

// be = Base Enemy
int behp[37], beatp[37], bedfp[37], bemp[37], bematp[37], bemdfp[37], bespd[37];
char ename[37][21];

// te = Temporary Enemy
int tehp[7], teatp[7], tedfp[7], temp[7], tematp[7], tehpmax[7], tempmax[7], televel[7], temdfp[7], tespd[7];
char tename[7][21];

////cordinate ints
int overx, overy, entertown, overcheck=2, towncheck, i;
float overdirection;

//Class Ranks
//1 = Fighter		2 = Acolyte		3 = Cleric		4 = Monk		5 = Thief		6 = Black Mage
//7 = Crusader		8 = Shaman		9 = Priest		10= Apprentice	11= Rogue		12= Dark Wizard
//13= Holy Warrior	14= Druid		15= High Priest	16= Master		17= Assassin	18= Necromancer
char charname[4][21], classname[19][21] = {" ", "Fighter", "Acolyte", "Cleric", "Monk", "Thief", "Black Mage", "Crusader", "Shaman", "Priest", "Apprentice", "Rogue", "Dark Wizard", "Holy Warrior", "Druid", "High Priest", "Master", "Assassin", "Necromancer"};

////town ints
float innchoice, bschoice, bsbuy, folkpick; 
int bschar, xxx;


////shop vars
int numpur,totalam, shoppick;

////church
int churchpick, k;

////dojo vars
int dojoclass, dojoclass2, dojoclass3, dojochar, train;

//***NEW***
//Dungeon Variables
int dungeonx, dungeony, step, dexitcheck, searchchoice, bosscheck;
//Dungeon Direction Limits
int dwestlimit[13] = {0, -4, -5, -4, -5, -4, -5, -4, -5, -4, -5, -4, -5};  
int deastlimit[13] = {0, 4, 5, 4, 5, 4, 5, 4, 5, 4, 5, 4, 5};  
int dnorthlimit[13] = {0, 4, 5, 4, 5, 4, 5, 4, 5, 4, 5, 4, 5};   
int dsouthlimit[13] = {0, -4, -5, -4, -5, -4, -5, -4, -5, -4, -5, -4, -5}; 
//Dungeon Entrances
int dexitx[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  
int dexity[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//Dungeon Weapons and Armor
int ditemx[13] = {0, -4, 5, 4, -5, -4, -5, 4, 5, 3, 4, 1, 1}; 
int ditemy[13] = {0, -4, 5, 4, -5, 4, 5, -4, -5, 1, -2, 2, -5};
int ditemcheck[13];
//Dungeon Keys and Bosses  
int dspecialx[13] = {0, 1, 2, 3, 4, -1, -2, -3, -4, 1, 2, 3, 4}; 
int dspecialy[13] = {0, -1, -2, -3, -4, 1, 2, 3, 4, 4, 3, 2, 1};
int dspecialcheck[13]; 

//Dungeon Names
char dungeonname[13][31] = {"", "Mallow Marsh", "Hidden Everglades", "Path of the Forgotten", "Cavern of the Lost", "Halls of the Dead", "Gateway to the Netherworld", "Boundless Desert", "Tomb of Tslor", "East Trails", "Mountainside", "Forest of Darkness", "Field of Death"};
//***END***


//***NEW***
//Boss Statistics
char bossname[7][21] = {"", "Swamp Monster", "Queen of Darkness", "Baelrog", "King Tslor", "Ancient Dragon", "Ent King"};
int bosshp[7] = {0, 10, 8, 12, 8, 12, 10};
int bossatp[7] = {0, 4, 3, 5, 3, 5, 4};
int bossdfp[7] = {0, 3, 4, 5, 4, 5, 3};
int bossmp[7] = {0, 0, 10, 0, 12, 4, 0};
int bossmatp[7] = {0, 0, 6, 0, 6, 4, 0};
int bossmdfp[7] = {0, 4, 6, 6, 6, 5, 5};
int bossspd[7] = {0, 2, 4, 3, 3, 3, 2};
//***END***





void overworld();
void overworldlocation();
void Lille();
void Karas();
void Briex();
void Ulm();
void Trevia();
void Rien();
void Inn();
void charcreate();
void basesetup();
void loadstats();
void newgamestory();
void karasstory();
void statcalc();
void status();
void battle();
void estatus();
void battlescreen();
void magicuse();
void spelleffect();
void itemuse();
void egenerator();
void sgenerator();
void edeath();
void shop();
void dojo();
void dojoname();
void church();
void dojocharselect();
void bgenerator();
void dungeonmain();
void healmagicuse();
void search();
void emagic();	
//blacksmith voids
void bsLille();
void bsRien();
void bsUlm();
void bsTrevia();
void bsKaras();
void bsBriex();
void bspurchase();
void bscharselect();
//Dungeon Voids
void BoundlessDesert();
void TombofTslor();	//Key 4
void CavernoftheLost();
void PathoftheForgotten(); //Key 2
void MallowMarsh(); //Key 1
void HiddenEverglades();
void HallsoftheDead();
void GatewaytotheNW(); //Key 3
void EastTrails();
void Mountainside(); //Key 5
void FieldofDeath();
void ForestofDarkness(); //Key 6




int main()
{
	srand((unsigned)time(NULL));
	cout.setf(ios::showpoint);
	cout.setf(ios::fixed);
	basesetup();

	do
	{
		system("CLS");
		cout<<"                 "<<"Dungeon Quest III: Torn Dreams\n";
		cout<<"\n";
		cout<<"Choose Your Destiny\n";
		cout<<"--------------------\n";
		cout<<"1.)New Game\n";
		cout<<"2.)Load Game\n";
		cout<<"3.)Quit\n";
		cout<<"Make your choice: ";
		cin>>neworload;
	
	if(neworload==1)
	{
		   for (i=1; i<=6; i++)
		   {
			   key[i]=0;
		   }
		
			newgamestory();
			overx=-7;
			overy=-6;
			overworld();


	}
	else if(neworload==2)
	{
	
		loadstats();
		overworld();


	}
	}
	while (neworload!=3);
	
	system("CLS");
	cout<<"Thank you for playing Dungeon Quest III\n";
	cout<<"Produced by: James Montemagno and Jason Sauppe\n";
	cout<<"Copyright 2005 CodeWarriors. All Rights Reserved.\n";
	cout<<"Press 1 to exit Dungeon Quest III: ";
	cin>>one;
	


	   return 0;
}



void overworld()
{


	do
	{	
		
		if(progress[0]==1)
		{
			if( ((progress[1]==1) || (progress[1]==2)) && ((progress[2]==1) || (progress[2]==2)) && ((progress[3]==1) || (progress[3]==2)) && ((progress[4]==1) || (progress[4]==2)) && ((progress[5]==1) || (progress[5]==2)) && ((progress[6]==1) || (progress[6]==2)) )
			{
				system("CLS");
				cout<<"Conclusion: The End is Near\n";
				cout<<"---------------------------\n";
				cout<<"Duke Vlad: "<<charname[1]<<", you have freed Neutria from the evil\n";
				cout<<"in the dungeons. We are forever in debt to you for all of your hard\n";
				cout<<"work. If it wasn't for you, our land would have been torn and ravaged.\n";
				cout<<" We shall have a celebration in your name.\n";
				cout<<"\n";
				cout<<"*You have recieved 100,000 G. for the completion of your journey.*\n";
				cout<<"\n";
				gold=gold+100000;
				cout<<"Press 1 to continue: ";
				cin>>one;
				system("CLS");
				cout<<"Conclusion: The End is Near\n";
				cout<<"---------------------------\n";
				cout<<"With your journey coming to an end, you are now content with yourself.\n";
				cout<<"You have proven that you are the strongest and most powerful "<<classname[charclass[1]]<<'\n';
				cout<<"A new journey now awaits you. You must find Maya your love once more.\n";
				cout<<"\n";
				cout<<"Press 1 to continue: ";
				cin>>one;
				system("CLS");
				cout<<"Congratulations for finishing Dungeon Quest III: Torn Dreams.\n";
				cout<<"On behalf of the development team. Thank you.\n";
				cout<<"\n";
				cout<<"Credits\n";
				cout<<"-------\n";
				cout<<"Lead Programmers:\n";
				cout<<"James Montemagno\n";
				cout<<"Jason Sauppe\n";
				cout<<"\n";
				cout<<"Story:\n";
				cout<<"James Montemagno\n";
				cout<<"\n";
				cout<<"Battle Engine:\n";
				cout<<"Jason Sauppe\n";
				cout<<"\n";
				cout<<"Special Thanks To:\n";
				cout<<"Mr. Weaver\n";
				cout<<"Everyone who made a cameo in the game(you know who you are).\n";
				cout<<"\n";
				cout<<"Press 1 to continue(Don't forget to save your game): ";
				cin>>one;
				progress[0]=2;
				

				
			}
		}

		if (neworload!=2)
		{
		system("CLS");
		cout<<"Neutria\n";
		towncheck=0;
		overworldlocation();
		cout<<"Choose Your Path\n";
		cout<<"----------------------------------\n";
		cout<<"1.)Travel North     2.)Travel East\n";
		cout<<"3.)Travel South     4.)Travel West\n";
		//done
		if( ((overx==-21) && (overy==-6)) || ((overx==-17) && (overy==4)) || ((overx==-3) && (overy==0)) || ((overx==11) && (overy==5)) || ((overx==22) && (overy==-6)) || ((overx==14) && (overy==-1)))  
		{
			cout<<"5.)Enter Town\n";
		
		}
		cout<<"Choose Your Path: ";
		cin>>overdirection;
		if(overdirection==1)
		{
			overy=overy+1;
			if(overy==8)
			{
				overy=overy-1;
			}
		
		}
		else if(overdirection==2)
		{
			overx=overx+1;
			if(overx==28)
			{
				overx=overx-1;
			}
		
		}
		else if(overdirection==3)
		{
			overy=overy-1;
			if(overy==-8)
			{
				overy=overy+1;
			}
		
		}
		else if(overdirection==4)
		{
			overx=overx-1;
			if(overx==-28)
			{
				overx=overx+1;
			}
			
		}
		else if(overdirection==5)
		{

			if(towncheck==1)
			{
				Lille();
			}
			else if(towncheck==2)
			{
				Karas();
			}
			else if(towncheck==3)
			{
				Briex();
			}
			else if(towncheck==4)
			{
				Ulm();
			}
			else if(towncheck==5)
			{
				Trevia();
			}
			else if(towncheck==6)
			{
				Rien();
			}
		}

		if( ((overx==23) && (overy==-6)) || ((overx==21) && (overy==-6)) || ((overx==24) && (overy==-5)) || ((overx==25) && (overy==-5)) || ((overx==26) && (overy==-5)) || ((overx==27) && (overy==-5)) || ((overx==20) && (overy==-5)) || ((overx==19) && (overy==-6)) || ((overx==18) && (overy==-6)) || ((overx==17) && (overy==-6)) || ((overx==16) && (overy==-6)) || ((overx==15) && (overy==-6)) || ((overx==14) && (overy==-6)) || ((overx==14) && (overy==-7)) || ((overx==22) && (overy==-7)) )
		{
			cout<<"You have fallen into the water, some HP has been depleted,\n";
			cout<<"so you return to the cabin for rest. Press 1 to continue: ";
			cin>>one;
			overx=-7;
			overy=-6;
		    for(i=1; i<=3; i++)
			{
		    		if (hp[i]>=0)
				{
					hp[i]=hp[i]-4;
				}
			}
			
		}
		}
		
		
		else if(neworload==2)
		{
		neworload=0;
		if(towncheck==1)
			{
				Lille();
			}
			else if(towncheck==2)
			{
				Karas();
			}
			else if(towncheck==3)
			{
				Briex();
			}
			else if(towncheck==4)
			{
				Ulm();
			}
			else if(towncheck==5)
			{
				Trevia();
			}
			else if(towncheck==6)
			{
				Rien();
			}
	}


		
		
	}
	while(overcheck!=1);


	
}


void Lille()
{
	if (progress[0]==0)
	{
		system("CLS");
		cout<<charname[2]<<": We first must travel to Karas.\n";
		cout<<charname[2]<<": My lord will explain the situation.\n";
		cout<<charname[2]<<": It is marked with a K on your map.\n";
		cout<<"\n";
		cout<<"Press 1 to continue: ";
		cin>>one;
	}

	else if(progress[0]>0)
	{


	do
	{
		system("CLS");
		cout<<"   -----------\n";
		cout<<"  *   Lille   *\n";
		cout<<"   -----------\n";
		cout<<"1.)Lady Kyra's Castle\n";
		cout<<"2.)Blacksmith\n";
		cout<<"3.)Alchemist\n";
		cout<<"4.)Pleasant Valley Inn\n";
		cout<<"5.)Lille House of Worship\n";
		cout<<"6.)Wizards' Keep\n";
		cout<<"7.)Talk to Townfolk\n";
		cout<<"8.)Leave for Dungeons\n";
		cout<<"9.)View Statistics\n";
		cout<<"10.)Leave Town\n";
		cout<<"11.)Quit Game\n";
		cout<<"-------------------\n";
		cout<<"Make your choice: ";
		cin>>townpick;
		if(townpick==1)
		{		
				system("CLS");
				cout<<"   -----------------------\n";
				cout<<"  *   Lady Kyra's Castle  *\n";
				cout<<"   -----------------------\n";
				if (progress[4]==0)
				{
					cout<<"Lady Kyra: The evil King Tslor lurks in the dungeon.\n";
					cout<<"Lady Kyra: He has ravaged our town for many years.\n";
					cout<<"Lady Krya: You must save us, by destroying him at all costs.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}
				else if(progress[4]==1)
				{
					cout<<"Lady Kyra: Thank you so much for slaying King Tslor.\n";
					cout<<"Lady Kyra: We are now free from his wrath. We are forever in debt to you.\n";
					cout<<"Lady Kyra: To show our appreciation please take a Elixer of Healing.\n";
					cout<<"Lady Kyra: Good luck on the rest of your journey.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
					progress[4]=2;
					itemnum[3]=itemnum[3]+1;
				}
				else if(progress[4]==2)
				{
					cout<<"Lady Kyra: Thank you again for freeing us from King Tslor.\n";
					cout<<"Lady Kyra: Good luck on teh rest of your journey.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}
		}
		else if(townpick==2)
		{
			bsLille();
		}
		else if(townpick==3)
		{
			shop();
		}
		else if(townpick==4)
		{
			Inn();
		}
		else if(townpick==5)
		{
			church();
		}
		else if(townpick==6)
		{
			dojo();
		}
		else if(townpick==7)
		{
			do
			{
				system("CLS");
				cout<<"  ----------\n";
				cout<<" * Townsfolk *\n";
				cout<<"  ----------\n";
				cout<<"1.)Perhala\n";
				cout<<"2.)Sauppe\n";
				cout<<"3.)Return to town\n";
				cout<<"Make your choice: ";
				cin>>folkpick;
				if(folkpick==1)
				{
					system("CLS");
					cout<<"  ----------------------------\n";
					cout<<" * Perhala: the Mighty Wizard *\n";
					cout<<"  ----------------------------\n";
					cout<<"Perhala: Cogito, Ergo Sum!\n";
					cout<<"Perhala: Fight the Power!\n";
					cout<<"Perhala: I>U\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}
				else if (folkpick==2)
				{
					system("CLS");
					cout<<"  ---------------------\n";
					cout<<" * Sauppe: the Warrior *\n";
					cout<<"  ---------------------\n";
					cout<<"Sauppe: Have you visited the town's dojo?\n";
					cout<<"Sauppe: At the dojo, the master will make you stronger for a small fee.\n";
					cout<<"Sauppe: It is essential to visit each dojo to continue your journey.\n";
					cout<<"Sauppe: Be aware that certain classes can only be trained in certain dojos\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}
			}
			while (folkpick!=3);



		}
		else if(townpick==8)
		{
			do
			{
				system("CLS");
				cout<<"  ----------------\n";
				cout<<" * Lille Dungeons *\n";
				cout<<"  ----------------\n";
				cout<<"1.)Boundless Desert\n";
				cout<<"2.)Tomb of Tslor*\n";
				cout<<"3.)Return to Town\n";
				cout<<"Make your choice: ";
				cin>>dungeonchoice;
				if(dungeonchoice==1)
				{
					BoundlessDesert();
				}
				else if(dungeonchoice==2)
				{
					system("CLS");
					cout<<"Tip:\n";
					cout<<"To find the boss in the dungeon, you must search your surroundings.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
					if(key[4]==0)
					{	
						system("CLS");
						cout<<"The Tomb of Tslor is locked, an emblem of a desert\n";
						cout<<"is carved into the door, next to the key hole.\n";
						cout<<"Find the key to enter the Tomb of Tslor, then return.\n";
						cout<<"\n";
						cout<<"Press 1 to return to dungeons: ";
						cin>>one;
					}
					else if(key[4]==1)
					{
						TombofTslor();
					}
				}
			}
			while(dungeonchoice!=3);
		}

		else if(townpick==9)
		{
			status();
		}
		
		else if(townpick==11)
		{
			townpick=10;
			overcheck=1;
			neworload=3;
		}

	}
	while(townpick!=10);
	}
}

void Karas()
{


	do
	{

		if (progress[0]==0)
		{
			
			karasstory();
			
		}


		system("CLS");
		cout<<"   -----------\n";
		cout<<"  *   Karas   *\n";
		cout<<"   -----------\n";
		cout<<"1.)Duke Vlad's Castle\n";
		cout<<"2.)Blacksmith\n";
		cout<<"3.)Alchemist\n";
		cout<<"4.)Cold Stone Inn\n";
		cout<<"5.)Karas Cathedral\n";
		cout<<"6.)Guild Hall\n";
		cout<<"7.)Talk to Townfolk\n";
		cout<<"8.)Leave for Dungeons\n";
		cout<<"9.)View Statistics\n";
		cout<<"10.)Leave Town\n";
		cout<<"11.)Quit Game\n";
		cout<<"-------------------\n";
		cout<<"Make your choice: ";
		cin>>townpick;
		if(townpick==1)
		{
			//progress 2
				system("CLS");
				cout<<"   -----------------------\n";
				cout<<"  *   Duke Vlad's Castle  *\n";
				cout<<"   -----------------------\n";
				if (progress[2]==0)
				{
					
					cout<<"Duke Vlad: A dark nemesis lurks in the Cavern of the Lost.\n";
					cout<<"Duke Vlad: We need your help in slaying this beast.\n";
					cout<<"Duke Vlad: After you have completed your task return to me,\n";
					cout<<"Duke Vlad: and I will reward you.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}
				else if(progress[2]==1)
				{
					cout<<"Duke Vlad: Thank you for slaying the Queen of Darkness.\n";
					cout<<"Duke Vlad: We are now free from her grasp. We may now live peaceful,\n";
					cout<<"Duke Vlad: one more. As a reward, please take 2500 G.\n";
					cout<<"Duke Vlad: Good Luck on the rest of your journey.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
					progress[2]=2;
					gold=gold+2500;
				}
				else if(progress[2]==2)
				{
					cout<<"Duke Vlad: Thank you again for slaying the Queen of Darkness.\n";
					cout<<"Duke Vlad: Good Luck on teh rest of your journey.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}

		}
		else if(townpick==2)
		{
			bsKaras();
		}
		else if(townpick==3)
		{
			shop();
		}
		else if(townpick==4)
		{
			Inn();
		}
		else if(townpick==5)
		{
			church();
		}
		else if(townpick==6)
		{
			dojo();
		}
		else if(townpick==7)
		{
			do
			{
				system("CLS");
				cout<<"  ----------\n";
				cout<<" * Townsfolk *\n";
				cout<<"  ----------\n";
				cout<<"1.)Condon\n";
				cout<<"2.)Mansfield\n";
				cout<<"3.)Return to town\n";
				cout<<"Make your choice: ";
				cin>>folkpick;
				if(folkpick==1)
				{
					system("CLS");
					cout<<"  ------------------------\n";
					cout<<" * Condon: the Apprentice *\n";
					cout<<"  ------------------------\n";
					cout<<"Condon: It is important to upgrade your weapons as soon as possible.\n";
					cout<<"Condon: If you don't upgrade your weapons you are sure to fail.\n";
					cout<<"Condon: You must be at a higher level to purchase weapons with a *\n";
					cout<<"Condon: by their name. Enemies will become easier once you obtain\n";
					cout<<"Condon: these weapons. Good Luck\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}
				else if (folkpick==2)
				{
					system("CLS");
					cout<<"  ---------------------\n";
					cout<<" * Mansfield: Retired Blacksmith *\n";
					cout<<"  ---------------------\n";
					cout<<"Mansfield: I used to be a blacksmith, back in the good old days.\n";
					cout<<"Mansfield: That was before the Unity of Steel was created. All of the\n";
					cout<<"Mansfield: blacksmiths came together and created set prices. This ended\n";
					cout<<"Mansfield: most competition, however sales skyrocketed.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}
			}
			while (folkpick!=3);

		}
		else if(townpick==8)
		{
			do
			{
				system("CLS");
				cout<<"  ----------------\n";
				cout<<" * Karas Dungeons *\n";
				cout<<"  ----------------\n";
				cout<<"1.)Path of the Forgotten\n";
				cout<<"2.)Cavern of the Lost*\n";
				cout<<"3.)Return to Town\n";
				cout<<"Make your choice: ";
				cin>>dungeonchoice;
				if(dungeonchoice==1)
				{
					PathoftheForgotten();
				}
				else if(dungeonchoice==2)
				{
					system("CLS");
					cout<<"Tip:\n";
					cout<<"To find the boss in the dungeon, you must search your surroundings.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;

					if(key[2]==0)
					{	
						system("CLS");
						cout<<"The Cavern of the Lost is locked, an emblem of a path\n";
						cout<<"is carved into the door, next to the key hole.\n";
						cout<<"Find the key to enter the Cavern of the Lost, then return.\n";
						cout<<"\n";
						cout<<"Press 1 to return to dungeons: ";
						cin>>one;
					}
					else if(key[2]==1)
					{
						CavernoftheLost();
					}
				}
			}
			while(dungeonchoice!=3);


		}
		else if(townpick==9)
		{
			status();

		}
		
		else if(townpick==11)
		{
			townpick=10;
			overcheck=1;
			neworload=3;
		}
		
	}
	while(townpick!=10);
}

void Briex()
{
	if (progress[0]==0)
	{
		system("CLS");
		cout<<charname[2]<<": We first must travel to Karas.\n";
		cout<<charname[2]<<": My lord will explain the situation.\n";
		cout<<charname[2]<<": It is marked with a K on your map.\n";
		cout<<"\n";
		cout<<"Press 1 to continue: ";
		cin>>one;
	}

	else if(progress[0]>0)
	{
	do
	{
		system("CLS");
		cout<<"   -----------\n";
		cout<<"  *   Briex   *\n";
		cout<<"   -----------\n";
		cout<<"1.)Lord Trieux's Castle\n";
		cout<<"2.)Blacksmith\n";
		cout<<"3.)Alchemist\n";
		cout<<"4.)Dreskil Inn\n";
		cout<<"5.)Cross of God\n";
		cout<<"6.)The Holy Arch\n";
		cout<<"7.)Talk to Townfolk\n";
		cout<<"8.)Leave for Dungeons\n";
		cout<<"9.)View Statistics\n";
		cout<<"10.)Leave Town\n";
		cout<<"11.)Quit Game\n";
		cout<<"-------------------\n";
		cout<<"Make your choice: ";
		cin>>townpick;
		if(townpick==1)
		{
			//progress 3
			system("CLS");
				cout<<"   -------------------------\n";
				cout<<"  *   Lord Trieux's Castle  *\n";
				cout<<"   -------------------------\n";
				if (progress[3]==0)
				{
					
					cout<<"Lord Trieux: Thank you for coming to our aid. Our town has been reavaged,\n";
					cout<<"Lord Trieux: multiple times, by the horrible Baelrog. Please destroy him.\n";
					cout<<"Lord Trieux: When you do, return to recieve a reward.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}
				else if(progress[3]==1)
				{
					cout<<"Lord Trieux: We are forever in debt to you for slaying the Baelrog.\n";
					cout<<"Lord Trieux: Please except an Extra Ether Potion as a gift.\n";
					cout<<"Lord Trieux: Good Luck on the rest of your journey.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
					progress[3]=2;
					itemnum[5]=itemnum[5]+1;
				}
				else if(progress[3]==2)
				{
					cout<<"Lord Trieux: We are forever in debt to you for slaying the Baelrog.\n";
					cout<<"Lord Trieux: Good Luck on the rest of your journey.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}
		}
		else if(townpick==2)
		{
			bsBriex();
		}
		else if(townpick==3)
		{
			shop();
		}
		else if(townpick==4)
		{
			Inn();
		}
		else if(townpick==5)
		{	
			church();
		}
		else if(townpick==6)
		{
			dojo();
		}
		else if(townpick==7)
		{
			do
			{
				system("CLS");
				cout<<"  ----------\n";
				cout<<" * Townsfolk *\n";
				cout<<"  ----------\n";
				cout<<"1.)Cheriyan\n";
				cout<<"2.)Frachenzio\n";
				cout<<"3.)Return to town\n";
				cout<<"Make your choice: ";
				cin>>folkpick;
				if(folkpick==1)
				{
					system("CLS");
					cout<<"  -----------------------\n";
					cout<<" * Cheriyan: Local Nurse *\n";
					cout<<"  -----------------------\n";
					cout<<"Cheriyan: I can not stress the importance of taking potions into battle.\n";
					cout<<"Cheriyan: I have seen many people come and go. The smartest warriors stock\n";
					cout<<"Cheriyan: stock up on potions at the Alchemist, before their journey.\n";
					cout<<"Cheriyan: Failure to do so may end in failure, as many have before.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}
				else if (folkpick==2)
				{
					system("CLS");
					cout<<"  ------------------------------\n";
					cout<<" * Frachenzio: Italian Merchant *\n";
					cout<<"  ------------------------------\n";
					cout<<"Frachenzio: I have traveled to many lands, and collected many items.\n";
					cout<<"Frachenzio: I have become a very rich man selling items to these townsfolk.\n";
					cout<<"Frachenzio: Money can only buy material goods, but you fight for happiness.\n";
					cout<<"Frachenzio: Remember this and you will become wealthier than me one day.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
					if (one==131514525)
					{
						system("CLS");
						cout<<"Frachenzio: You have broken my code, congratulations!\n";
						cout<<"Frachenzio: As a reward, 10,000 G!\n";
						cout<<"\n";
						cout<<"Press 1 to continue\n";
						cin>>one;
						gold=gold+10000;
					}

				}
			}
			while (folkpick!=3);

		}
		else if(townpick==8)
		{

			do
			{
				system("CLS");
				cout<<"  ----------------\n";
				cout<<" * Briex Dungeons *\n";
				cout<<"  ----------------\n";
				cout<<"1.)Halls of the Dead\n";
				cout<<"2.)Gateway to the NetherWorld*\n";
				cout<<"3.)Return to Town\n";
				cout<<"Make your choice: ";
				cin>>dungeonchoice;
				if(dungeonchoice==1)
				{
					HallsoftheDead();
				}
				else if(dungeonchoice==2)
				{
					system("CLS");
					cout<<"Tip:\n";
					cout<<"To find the boss in the dungeon, you must search your surroundings.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
					if(key[3]==0)
					{	
						system("CLS");
						cout<<"The Gateway to the NetherWorld is locked, an emblem of a tomb\n";
						cout<<"is carved into the door, next to the key hole.\n";
						cout<<"Find the key to enter the Gateway to the NetherWorld, then return.\n";
						cout<<"\n";
						cout<<"Press 1 to return to dungeons: ";
						cin>>one;
					}
					else if(key[3]==1)
					{
						GatewaytotheNW();
					}
				}
			}
			while(dungeonchoice!=3);
		}
		else if(townpick==9)
		{
			status();
		}
		
		else if(townpick==11)
		{
			townpick=10;
			overcheck=1;
			neworload=3;
		}
	}
	while(townpick!=10);
	}

}

void Ulm()
{
	if (progress[0]==0)
	{
		system("CLS");
		cout<<charname[2]<<": We first must travel to Karas.\n";
		cout<<charname[2]<<": My lord will explain the situation.\n";
		cout<<charname[2]<<": It is marked with a K on your map.\n";
		cout<<"\n";
		cout<<"Press 1 to continue: ";
		cin>>one;
	}

	else if(progress[0]>0)
	{
	do
	{
		system("CLS");
		cout<<"   ---------\n";
		cout<<"  *   Ulm   *\n";
		cout<<"   ---------\n";
		cout<<"1.)Sir Ferchenzio\n";
		cout<<"2.)Blacksmith\n";
		cout<<"3.)Alchemist\n";
		cout<<"4.)Ulm Requiem\n";
		cout<<"5.)First Ulm Church\n";
		cout<<"6.)Ys Dojo\n";
		cout<<"7.)Talk to Townfolk\n";
		cout<<"8.)Leave for Dungeons\n";
		cout<<"9.)View Statistics\n";
		cout<<"10.)Leave Town\n";
		cout<<"11.)Quit Game\n";
		cout<<"-------------------\n";
		cout<<"Make your choice: ";
		cin>>townpick;
		if(townpick==1)
		{
			//progress 5
			system("CLS");
				cout<<"   -------------------\n";
				cout<<"  *   Sir Ferchenzio  *\n";
				cout<<"   -------------------\n";
				if (progress[5]==0)
				{
					
					cout<<"Sir Ferchenzio: The Ancient Dragon flies high over our small city.\n";
					cout<<"Sir Ferchenzio: You must help us and rid him from our skies.\n";
					cout<<"Sir Ferchenzio: After the Ancient Dragon is slayed return for a reward.\n";
					cout<<"Sir Ferchenzio: If you are low on gold, visit my cousin. He should be\n";
					cout<<"Sir Ferchenzio: around on of the local towns. Break his code.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}
				else if(progress[5]==1)
				{
					cout<<"Sir Ferchenzio: Thank you for slaying the Ancient Dragon.\n";
					cout<<"Sir Ferchenzio: We are now able to live in peace once more.\n";
					cout<<"Sir Ferchenzio: Take 2000 G as a reward.\n";
					cout<<"Sir Ferchenzio: Good Luck on the rest of your journey.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
					progress[5]=2;
					gold=gold+2000;
				}
				else if(progress[5]==2)
				{
					cout<<"Sir Ferchenzio: Thank you for slaying the Ancient Dragon.\n";
					cout<<"Sir Ferchenzio: We are now able to live in peace once more.\n";
					cout<<"Sir Ferchenzio: Good Luck on the rest of your journey.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}

		}
		else if(townpick==2)
		{
			bsUlm();
		}
		else if(townpick==3)
		{
			shop();
		}
		else if(townpick==4)
		{
			Inn();
		}
		else if(townpick==5)
		{
			church();
		}
		else if(townpick==6)
		{
			dojo();
		}
		else if(townpick==7)
		{
			do
			{
				system("CLS");
				cout<<"  ----------\n";
				cout<<" * Townsfolk *\n";
				cout<<"  ----------\n";
				cout<<"1.)Weaver\n";
				cout<<"2.)Graham\n";
				cout<<"3.)Return to town\n";
				cout<<"Make your choice: ";
				cin>>folkpick;
				if(folkpick==1)
				{
					system("CLS");
					cout<<"  -----------------\n";
					cout<<" * Weaver: Chemist *\n";
					cout<<"  -----------------\n";
					cout<<"Weaver: I am currently working on a way to combine multiple potions together.\n";
					cout<<"Weaver: It will revolutionize the way battles are fought. However,\n";
					cout<<"Weaver: I feel as though I am years away from completing the research.\n";
					cout<<"Weaver: Wish me luck.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}
				else if (folkpick==2)
				{
					system("CLS");
					cout<<"  -------------------\n";
					cout<<" * Graham: Blackbelt *\n";
					cout<<"  -------------------\n";
					cout<<"Graham: I have trained for years, and now I am a blackbelt.\n";
					cout<<"Graham: There is a tournament held every year in Lille to find\n";
					cout<<"Graham: the worlds best karate champion.\n";
					cout<<"Graham: I have no fear, I will surely sweep the competition.\n";
					cout<<"Graham: Good luck in your journey.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}
			}
			while (folkpick!=3);

		}
		else if(townpick==8)
		{
			do
			{
				system("CLS");
				cout<<"  --------------\n";
				cout<<" * Ulm Dungeons *\n";
				cout<<"  --------------\n";
				cout<<"1.)East Trails\n";
				cout<<"2.)Mountainside*\n";
				cout<<"3.)Return to Town\n";
				cout<<"Make your choice: ";
				cin>>dungeonchoice;
				if(dungeonchoice==1)
				{
					EastTrails();
				}
				else if(dungeonchoice==2)
				{
					system("CLS");
					cout<<"Tip:\n";
					cout<<"To find the boss in the dungeon, you must search your surroundings.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
					if(key[5]==0)
					{	
						system("CLS");
						cout<<"The Mountainside is locked, an emblem of a trail\n";
						cout<<"is carved into the door, next to the key hole.\n";
						cout<<"Find the key to enter the Mountainside, then return.\n";
						cout<<"\n";
						cout<<"Press 1 to return to dungeons: ";
						cin>>one;
					}
					else if(key[5]==1)
					{
						Mountainside();
					}
				}
			}
			while(dungeonchoice!=3);
		}
		else if(townpick==9)
		{
			status();
		}
		
		else if(townpick==11)
		{
			townpick=10;
			overcheck=1;
			neworload=3;
		}
	}
	while(townpick!=10);
	}
							  
}

void Trevia()
{
	if (progress[0]==0)
	{
		system("CLS");
		cout<<charname[2]<<": We first must travel to Karas.\n";
		cout<<charname[2]<<": My lord will explain the situation.\n";
		cout<<charname[2]<<": It is marked with a K on your map.\n";
		cout<<"\n";
		cout<<"Press 1 to continue: ";
		cin>>one;
	}

	else if(progress[0]>0)
	{
	do
	{
		system("CLS");
		cout<<"   ------------\n";
		cout<<"  *   Trevia   *\n";
		cout<<"   ------------\n";
		cout<<"1.)King Sigurd's Castle\n";
		cout<<"2.)Blacksmith\n";
		cout<<"3.)Alchemist\n";
		cout<<"4.)Trevia Inn\n";
		cout<<"5.)Church of Trevia\n";
		cout<<"6.)Hidden Grotto\n";
		cout<<"7.)Talk to Townfolk\n";
		cout<<"8.)Leave Dungeons\n";
		cout<<"9.)View Statistics\n";
		cout<<"10.)Leave Town\n";
		cout<<"11.)Quit Game\n";
		cout<<"-------------------\n";
		cout<<"Make your choice: ";
		cin>>townpick;
		if(townpick==1)
		{
			//progress 6
			system("CLS");
				cout<<"   -------------------------\n";
				cout<<"  *   King Sigurd's Castle  *\n";
				cout<<"   -------------------------\n";
				if (progress[6]==0)
				{
					
					cout<<"King Sigurd: A horrible Ent has been terrorizing our town.\n";
					cout<<"King Sigurd: Please destroy it, and I will reward you.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}
				else if(progress[6]==1)
				{
					cout<<"King Sigurd: Thank you for slaying the Ent. The town is at peace\n";
					cout<<"King Sigurd: once more. We are in debt to you.\n";
					cout<<"King Sigurd: Please take 3 Healing Potions for your work.\n";
					cout<<"King Sigurd: Good Luck on the rest of your journey.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
					progress[6]=2;
					itemnum[1]=itemnum[1]+3;
				}
				else if(progress[6]==2)
				{
					cout<<"King Sigurd: Thank you for slaying the Ent.\n";
					cout<<"King Sigurd: Good Luck on the rest of your journey.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}
		}
		else if(townpick==2)
		{
			bsTrevia();
		}
		else if(townpick==3)
		{ 
			shop();
		}
		else if(townpick==4)
		{
			Inn();
		}
		else if(townpick==5)
		{
			church();
		}
		else if(townpick==6)
		{ 
			dojo();
		}
		else if(townpick==7)
		{
			do
			{
				system("CLS");
				cout<<"  ----------\n";
				cout<<" * Townsfolk *\n";
				cout<<"  ----------\n";
				cout<<"1.)Goodfellow\n";
				cout<<"2.)Aloi\n";
				cout<<"3.)Return to town\n";
				cout<<"Make your choice: ";
				cin>>folkpick;
				if(folkpick==1)
				{
					system("CLS");
					cout<<"  ----------------------------\n";
					cout<<" * Goodfellow: the Troubadour *\n";
					cout<<"  ----------------------------\n";
					cout<<"Goodfellow: I have traveled town to town signing and reciting poetry.\n";
					cout<<"Goodfellow: The townsfolk love me for my talent. However the Italian\n";
					cout<<"Goodfellow: Merchant in Briex was the most impressed. I was able to solve\n";
					cout<<"Goodfellow: his code, and he gave me 10,000 G. Good Luck.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}
				else if (folkpick==2)
				{
					system("CLS");
					cout<<"  -------------------------\n";
					cout<<" * Aloi: The Mathematician *\n";
					cout<<"  -------------------------\n";
					cout<<"Aloi: A^2+B^2=C^2\n";
					cout<<"Aloi: X= (-B+-sqrt(B^2-4AC))/2A\n";
					cout<<"Aloi: Parametrics are fun for everyone.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}
			}
			while (folkpick!=3);

		}
		else if(townpick==8)
		{
			do
			{
				system("CLS");
				cout<<"  -----------------\n";
				cout<<" * Trevia Dungeons *\n";
				cout<<"  -----------------\n";
				cout<<"1.)Field of Death\n";
				cout<<"2.)Forest of Darkness*\n";
				cout<<"3.)Return to Town\n";
				cout<<"Make your choice: ";
				cin>>dungeonchoice;
				if(dungeonchoice==1)
				{
					FieldofDeath();
				}
				else if(dungeonchoice==2)
				{
					system("CLS");
					cout<<"Tip:\n";
					cout<<"To find the boss in the dungeon, you must search your surroundings.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
					if(key[6]==0)
					{	
						system("CLS");
						cout<<"The Forest of Darkness is locked, an emblem of grass\n";
						cout<<"is carved into the door, next to the key hole.\n";
						cout<<"Find the key to enter the Forest of Darkness, then return.\n";
						cout<<"\n";
						cout<<"Press 1 to return to dungeons: ";
						cin>>one;
					}
					else if(key[6]==1)
					{
						ForestofDarkness();
					}
				}
			}
			while(dungeonchoice!=3);
		}
		else if(townpick==9)
		{
			status();
		}
		
		else if(townpick==11)
		{
			townpick=10;
			overcheck=1;
			neworload=3;
		}
	}
	while(townpick!=10);
	}
	

}

void Rien()
{
	if (progress[0]==0)
	{
		system("CLS");
		cout<<charname[2]<<": We first must travel to Karas.\n";
		cout<<charname[2]<<": My lord will explain the situation.\n";
		cout<<charname[2]<<": It is marked with a K on your map.\n";
		cout<<"\n";
		cout<<"Press 1 to continue: ";
		cin>>one;
	}

	else if(progress[0]>0)
	{
	do
	{
		system("CLS");
		cout<<"   ----------\n";
		cout<<"  *   Rien   *\n";
		cout<<"   ----------\n";
		cout<<"1.)King James' Castle\n";
		cout<<"2.)Blacksmith\n";
		cout<<"3.)Alchemist\n";
		cout<<"4.)Rien Inn\n";
		cout<<"5.)Holy Rien\n";
		cout<<"6.)Kyme's Place\n";
		cout<<"7.)Talk to Townfolk\n";
		cout<<"8.)Leave for Dungeons\n";
		cout<<"9.)View Statistics\n";
		cout<<"10.)Leave Town\n";
		cout<<"11.)Quit Game\n";
		cout<<"-------------------\n";
		cout<<"Make your choice: ";
		cin>>townpick;
		if(townpick==1)
		{
			//progress 1
			system("CLS");
				cout<<"   -----------------------\n";
				cout<<"  *   King James' Castle  *\n";
				cout<<"   -----------------------\n";
				if (progress[1]==0)
				{
					
					cout<<"King James: I have sent many men to try to destroy the Swamp Monster.\n";
					cout<<"King James: All attempts have ended with failure. I will handsomely\n";
					cout<<"King James: reward you if you are able to destroy it.\n";
					cout<<"King James: May be force be with you.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}
				else if(progress[1]==1)
				{
					cout<<"King James: Good work, you have succeeded where many have failed.\n";
					cout<<"King James: You are truely a god among men. Please accept\n";
					cout<<"King James: 2 Resurrection Vials for you hard work.\n";
					cout<<"King James: Good Luck on the rest of your journey.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
					progress[1]=2;
					itemnum[6]=itemnum[6]+2;
				}
				else if(progress[1]==2)
				{
					cout<<"King James: Thank you again for you hard work.\n";
					cout<<"King James: Good Luck on the rest of your journey.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}
		}
		else if(townpick==2)
		{
			bsRien();
		}
		else if(townpick==3)
		{ 
			shop();
		}
		else if(townpick==4)
		{
			Inn();
		}
		else if(townpick==5)
		{
			church();
		}
		else if(townpick==6)
		{
			dojo();
		}
		else if(townpick==7)
		{

			do
			{
				system("CLS");
				cout<<"  ----------\n";
				cout<<" * Townsfolk *\n";
				cout<<"  ----------\n";
				cout<<"1.)Gill\n";
				cout<<"2.)Harrington\n";
				cout<<"3.)Return to town\n";
				cout<<"Make your choice: ";
				cin>>folkpick;
				if(folkpick==1)
				{
					system("CLS");
					cout<<"  ---------------------\n";
					cout<<" * Gill: The Fisherman *\n";
					cout<<"  ---------------------\n";
					cout<<"Gill: To find a fish in water, you must find the angle of refraction.\n";
					cout<<"Gill: If you fail to do this, you will hit behind the fish.\n";
					cout<<"Gill: This mostly due to the index of refraction, going from low to high.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}
				else if (folkpick==2)
				{
					system("CLS");
					cout<<"  -------------------------\n";
					cout<<" * Harrington: The Peasant *\n";
					cout<<"  -------------------------\n";
					cout<<"Harrington: It is important to study your enemies, and find their weaknesses.\n";
					cout<<"Harrington: This will allow you to use less magic during your battles.\n";
					cout<<"Harrington: Don't forget that you can restore your HP and MP in the Inn.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
				}
			}
			while (folkpick!=3);


		}
		else if(townpick==8)
		{
			do
			{
				system("CLS");
				cout<<"  ----------------\n";
				cout<<" * Rien Dungeons *\n";
				cout<<"  ----------------\n";
				cout<<"1.)Mallow Marsh\n";
				cout<<"2.)Hidden Everglades*\n";
				cout<<"3.)Return to Town\n";
				cout<<"Make your choice: ";
				cin>>dungeonchoice;
				if(dungeonchoice==1)
				{
					MallowMarsh();
				}
				else if(dungeonchoice==2)
				{
					system("CLS");
					cout<<"Tip:\n";
					cout<<"To find the boss in the dungeon, you must search your surroundings.\n";
					cout<<"\n";
					cout<<"Press 1 to continue: ";
					cin>>one;
					if(key[1]==0)
					{	
						system("CLS");
						cout<<"The Hidden Everglades are locked, an emblem of a swamp\n";
						cout<<"are carved into the door, next to the key hole.\n";
						cout<<"Find the key to enter the Hidden Everglades, then return.\n";
						cout<<"\n";
						cout<<"Press 1 to return to dungeons: ";
						cin>>one;
					}
					else if(key[1]==1)
					{
						HiddenEverglades();
					}
				}
			}
			while(dungeonchoice!=3);
		}
		else if(townpick==9)
		{
			status();
		}
		
		else if(townpick==11)
		{
			townpick=10;
			overcheck=1;
			neworload=3;
		}
	}
	while(townpick!=10);
	}
}







void Inn()
{
	do
	{
	 system("CLS");
	 if(towncheck==1)
	 {
		 cout<<"  -------------------------      -------------\n";
		 cout<<" *   Pleasant Valley Inn   *     Gold: "<<gold<<"\n";
		 cout<<"  -------------------------      -------------\n";
		 cout<<"   Options            Price\n";
		 cout<<"------------------------------\n";
		 cout<<"1.)Spend the Night    30 Gold \n";
	 }
	 else if(towncheck==2)
	 {
		 cout<<"  --------------------      -------------\n";
		 cout<<" *   Cold Stone Inn   *     Gold: "<<gold<<"\n";
		 cout<<"  --------------------      -------------\n";
		 cout<<"   Options            Price\n";
		 cout<<"------------------------------\n";
		 cout<<"1.)Spend the Night    40 Gold \n";
	 }
	 else if(towncheck==3)
	 {
		 cout<<"  -----------------      -------------\n";
		 cout<<" *   Dreskil Inn   *     Gold: "<<gold<<"\n";
		 cout<<"  -----------------      -------------\n";
		 cout<<"   Options            Price\n";
		 cout<<"------------------------------\n";
		 cout<<"1.)Spend the Night    75 Gold \n";
	 }
	 else if(towncheck==4)
	 {
		 cout<<"  -----------------      -------------\n";
		 cout<<" *   Ulm Requiem   *     Gold: "<<gold<<"\n";
		 cout<<"  -----------------      -------------\n";
		 cout<<"   Options            Price\n";
		 cout<<"------------------------------\n";
		 cout<<"1.)Spend the Night    50 Gold \n";
	 }
	 else if(towncheck==5)
	 {
		 cout<<"  ----------------      -------------\n";
		 cout<<" *   Trevia Inn   *     Gold: "<<gold<<"\n";
		 cout<<"  ----------------      -------------\n";
		 cout<<"   Options            Price\n";
		 cout<<"------------------------------\n";
		 cout<<"1.)Spend the Night    80 Gold \n";
	 }
	 else if(towncheck==6)
	 {
		 cout<<"  --------------      ------------\n";
		 cout<<" *   Rien Inn   *     Gold: "<<gold<<"\n";
		 cout<<"  --------------      -------------\n";
		 cout<<"   Options            Price\n";
		 cout<<"------------------------------\n";
		 cout<<"1.)Spend the Night    55 Gold \n";
	 }
		 cout<<"2.)Save	Game          Free\n";
		 cout<<"3.)Leave Inn\n";
		 cout<<"------------------------------\n";
		 cout<<"Make your choice: ";
		 cin>>innchoice;
		 if(innchoice==1)
		 {
			 system("CLS");
			 if(towncheck==1)
			 {
				
				cout<<"  -------------------------\n";
				cout<<" *   Pleasant Valley Inn   *\n";
				cout<<"  -------------------------\n";
				 if(gold>=30)
				 {
					gold=gold-30;
					
					cout<<"Concierge: Thank you for staying the night, I hope you all slept well.\n";
					cout<<"*Your health and magic has been replenished.\n";
					for (i=1; i<=3; i++)
					{
						if(hp[i]>0)
						{
							hp[i]=uchpmax[i];
							mp[i]=ucmpmax[i];
						}
					}
					
					
				 }
				 else if(gold<30)
				 {
					 cout<<"Concierge: You do not have enough gold to spend the night\n";
				 }
			 }
			 else if(towncheck==2)
			 {
				 
				 cout<<"  --------------------\n";
				 cout<<" *   Cold Stone Inn   *\n";
				 cout<<"  --------------------\n";
				 if (gold>=40)
				 {
					gold=gold-40;
					cout<<"Concierge: Thank you for staying the night, I hope you all slept well.\n";
					cout<<"*Your health and magic has been replenished.\n";
					for (i=1; i<=3; i++)
					{
						if(hp[i]>0)
						{
							hp[i]=uchpmax[i];
							mp[i]=ucmpmax[i];
						}
					}
				 }
				 else if(gold<40)
				 {
					 cout<<"Concierge: You do not have enough gold to spend the night\n";
				 }

			 }
			 else if(towncheck==3)
			 {
				 
				 cout<<"  -----------------\n";
				 cout<<" *   Dreskil Inn   *\n";
				 cout<<"  -----------------\n";
				 if (gold>=75)
				 {
					gold=gold-75;
					cout<<"Concierge: Thank you for staying the night, I hope you all slept well.\n";
					cout<<"*Your health and magic has been replenished.\n";
					for (i=1; i<=3; i++)
					{
						if(hp[i]>0)
						{
							hp[i]=uchpmax[i];
							mp[i]=ucmpmax[i];
						}
					}
				 }
				 else if(gold<75)
				 {
					 cout<<"Concierge: You do not have enough gold to spend the night\n";
				 }
			 }
			 else if(towncheck==4)
			 {
				 
				 cout<<"  -----------------\n";
				 cout<<" *   Ulm Requiem   *\n";
				 cout<<"  -----------------\n";
				 if (gold>=50)
				 {
					gold=gold-50;
					cout<<"Concierge: Thank you for staying the night, I hope you all slept well.\n";
					cout<<"*Your health and magic has been replenished.\n";
					for (i=1; i<=3; i++)
					{
						if(hp[i]>0)
						{
							hp[i]=uchpmax[i];
							mp[i]=ucmpmax[i];
						}
					}
				 }
				 else if(gold<50)
				 {
					 cout<<"Concierge: You do not have enough gold to spend the night\n";
				 }
			 }
			 else if(towncheck==5)
			 {
				 
				 cout<<"  ----------------\n";
				 cout<<" *   Trevia Inn   *\n";
				 cout<<"  ----------------\n";
				 if (gold>=80)
				 {
					gold=gold-80;
					cout<<"Concierge: Thank you for staying the night, I hope you all slept well.\n";
					cout<<"*Your health and magic has been replenished.\n";
					for (i=1; i<=3; i++)
					{
						if(hp[i]>0)
						{
							hp[i]=uchpmax[i];
							mp[i]=ucmpmax[i];
						}
					}
				 }
				 else if(gold<80)
				 {
					 cout<<"Concierge: You do not have enough gold to spend the night\n";
				 }
			 }
			 else if(towncheck==6)
			 {
				 
				 cout<<"  --------------\n";
				 cout<<" *   Rien Inn   *\n";
				 cout<<"  --------------\n";
				 if (gold>=55)
				 {
					gold=gold-55;
					cout<<"Concierge: Thank you for staying the night, I hope you all slept well.\n";
					cout<<"*Your health and magic has been replenished.\n";
					for (i=1; i<=3; i++)
					{
						if(hp[i]>0)
						{
							hp[i]=uchpmax[i];
							mp[i]=ucmpmax[i];
						}
					}
				 }
				 else if(gold<55)
				 {
					 cout<<"Concierge: You do not have enough gold to spend the night\n";
				 }
			 }
			 cout<<"\n";
			 cout<<"Press 1 to return to the hotel front desk: ";
			 cin>>one;

			 
			 
		 }
		 else if(innchoice==2)
		 {

			 //Read User Character Stats
		ofstream charfile;
		charfile.open("charfile.dat", ios::out);
		for(i = 1; i < 4; i++)
		{
			charfile << charname[i]<<endl;
			charfile << charclass[i]<<endl;
			charfile << hp[i]<<endl;
			charfile << mp[i]<<endl;
			charfile << level[i]<<endl;
			charfile << xp[i]<<endl;
			charfile << reqxp[i]<<endl;
			charfile << weapon[i]<<endl;
			charfile << armor[i]<<endl;
			charfile << maleorfemale[i]<<endl;
			
		}	


			charfile.close();

			//Read User Character Stats
			ofstream infile;
			infile.open("motz.dat", ios::out);
			
			infile<<gold<<endl;
			infile<<overx<<endl;
			infile<<overy<<endl;
			for(i=0; i<=6; i++)
			{
			infile<<progress[i]<<endl;
			}
			infile<<overdirection<<endl;
			infile<<towncheck<<endl;
			for(i=1; i<=6; i++)
			{
				infile<<key[i]<<endl;
			}
			for(i = 1; i < 7; i++)
			{
				infile << itemnum[i] << endl;
			}


			infile.close();

			ofstream dsearch;
			dsearch.open("dsearch.dat", ios:: out);
			for (i=1; i<=12; i++)
			{
				dsearch<<ditemcheck[i]<<endl;
				dsearch<<dspecialcheck[i]<<endl;
			}
			dsearch.close();



			system("CLS");
			cout<<"Your progress has been saved\n";
			cout<<"\n";
			cout<<"Press 1 to return to the hotel front desk: ";
			cin>>one;

			 
		 }


	}
	while(innchoice!=3);
}
		 





void overworldlocation()
{	
	map.overx=overx;
	map.overy=overy;
	map.towncheck=towncheck;
	map.map();
	towncheck=map.towncheck;

	
}

//Blacksmiths
void bsLille()
{
	do
	{
	   system("CLS");
	   cout<<"  -----------------------\n";
	   cout<<" * Wagner the Blacksmith *\n";
	   cout<<"  -----------------------\n";
	   cout<<" Options\n";
	   cout<<"-------------------------\n";
	   cout<<"1.)Buy\n";
	   cout<<"2.)Leave Blacksmith\n";
	   cout<<"-------------------------\n";
	   cout<<"Make your choice: ";
	   cin>>bschoice;
	   

	   
	   if (bschoice==1)
	   {
		   bscharselect();
		   cout<<"Select a Character: ";
		   cin>>bschar;
		   i=bschar;

		   do
		   {
			system("CLS");
			cout<<"  -----------------------      -------------\n";
			cout<<" * Wagner the Blacksmith *     Gold: "<<gold<<"\n";
			cout<<"  -----------------------      -------------\n";
			cout<<"   Weapon             Price  |    Armor               Price\n";
			cout<<"-----------------------------------------------------------\n";
			cout<<"1.)Long Sword(F)     1000 G  | 8.)Steel Plate(F)     1300 G\n";
			cout<<"2.)Warhammer(A)       975 G  | 9.)Raw Hide Suit(A)    990 G\n";
			cout<<"3.)Mace(C)            850 G  | 10.)Chain Mail(C)      750 G\n";
			cout<<"4.)Brass Knuckles(M)  800 G  | 11.)Trainer's Suit(M)  880 G\n";
			cout<<"5.)Short Sword(T)     725 G  | 12.)Leather Armor(T)   800 G\n";
			cout<<"6.)Dagger(D)          650 G  | 13.)Mage's Robe(D)    1000 G\n";
			cout<<"7.)Quarter Staff(D)* 5500 G  | 14.)Elder's Cloak(D)* 4800 G\n";
			cout<<"Make your choice(press 0 to return to shop): ";
			cin>>bsbuy;

			bspurchase();
			if(bsbuy==7)
			{	
				    if (charclass[i]==6)
					{
						system("CLS");
						if(level[i]>=15)
						{
							if(weapon[i]==17)
							{
								cout<<"BS: You already have this weapon equiped.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(weapon[i]>17)
						{
							cout<<"BS: You already have a more powerful weapon.";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
							else
							{
						
								if(gold<5500)
								{	
									cout<<"BS: You do not have enough gold to purchase that.\n";
									cout<<"BS: You must	slay more enemies in the dungeons.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
								}
								else if(gold>=5500)
								{
									gold=gold-5500;
									cout<<"BS: Thank you for purchasing the Quarter Staff,\n";
									cout<<"BS: it shall treat you well on your journey.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
									weapon[i]=17;
									statcalc();
								}
							}
						}
						else if(level[i]<15)
						{
							cout<<"BS: You are not able to handle this weapon yet.\n";
							cout<<"BS: Slay more enemies and become stonger, then return\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
					}
					else if(charclass[i]!=6)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}

			else if(bsbuy==14)
			{	
				    if (charclass[i]==6)
					{
						system("CLS");
						if(level[i]>=15)
						{
							if(armor[i]==17)
							{
								cout<<"BS: You already have this armor equiped.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}		
							else if(armor[i]>17)
						{
							cout<<"BS: You already have more powerful armor.";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
							else
							{
						
								if(gold<4800)
								{	
									cout<<"BS: You do not have enough gold to purchase that.\n";
									cout<<"BS: You must	slay more enemies in the dungeons.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
								}
								else if(gold>=4800)
								{
									gold=gold-4800;
									cout<<"BS: Thank you for purchasing the Elder's Cloak,\n";
									cout<<"BS: it shall treat you well on your journey.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
									armor[i]=17;
									statcalc();
								}
							}
						}
						else if(level[i]<15)
						{
							cout<<"BS: You are not able to handle this armor yet.\n";
							cout<<"BS: Slay more enemies and become stonger, then return\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
					}
					else if(charclass[i]!=6)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}


			  i=bschar;


					
		   }
		   while(bsbuy!=0);

	 }



	}
	while (bschoice!=2);
}



void bsKaras()
{
	do
	{
	   system("CLS");
	   cout<<"  -----------------------\n";
	   cout<<" * Helmer the Blacksmith *\n";
	   cout<<"  -----------------------\n";
	   cout<<" Options\n";
	   cout<<"-------------------------\n";
	   cout<<"1.)Buy\n";
	   cout<<"2.)Leave Blacksmith\n";
	   cout<<"-------------------------\n";
	   cout<<"Make your choice: ";
	   cin>>bschoice;
	   

	   
	   if (bschoice==1)
	   {
		   bscharselect();
		   cout<<"Select a Character: ";
		   cin>>bschar;
		   i=bschar;

		   do
		   {
			system("CLS");
			cout<<"  -----------------------      -------------\n";
			cout<<" * Helmer the Blacksmith *     Gold: "<<gold<<"\n";
			cout<<"  -----------------------      -------------\n";
			cout<<"   Weapon              Price   |    Armor                Price\n";
			cout<<"---------------------------------------------------------------\n";
			cout<<"1.)Long Sword(F)       1000 G  | 8.)Steel Plate(F)       1300 G\n";
			cout<<"2.)Warhammer(A)         975 G  | 9.)Raw Hide Suit(A)      990 G\n";
			cout<<"3.)Mace(C)              850 G  | 10.)Chain Mail(C)        750 G\n";
			cout<<"4.)Brass Knuckles(M)    800 G  | 11.)Trainer's Suit(M)    880 G\n";
			cout<<"5.)Short Sword(T)       725 G  | 12.)Leather Armor(T)     800 G\n";
			cout<<"6.)Dagger(D)            650 G  | 13.)Mage's Robe(D)      1000 G\n";
			cout<<"7.)Lightning Sword(T)* 5000 G  | 14.)Studded Leather(T)* 4200 G\n";
			cout<<"Make your choice(press 0 to return to shop): ";
			cin>>bsbuy;

			bspurchase();
			if(bsbuy==7)
			{	
				    if (charclass[i]==5)
					{
						system("CLS");
						if(level[i]>=15)
						{
							if(weapon[i]==14)
							{
								cout<<"BS: You already have this weapon equiped.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(weapon[i]>14)
						{
							cout<<"BS: You already have a more powerful weapon.";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
							else
							{
						
								if(gold<5000)
								{	
									cout<<"BS: You do not have enough gold to purchase that.\n";
									cout<<"BS: You must	slay more enemies in the dungeons.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
								}
								else if(gold>=5000)
								{
									gold=gold-5000;
									cout<<"BS: Thank you for purchasing the Lightning Sword,\n";
									cout<<"BS: it shall treat you well on your journey.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
									weapon[i]=14;
									statcalc();
								}
							}
						}
						else if(level[i]<15)
						{
							cout<<"BS: You are not able to handle this weapon yet.\n";
							cout<<"BS: Slay more enemies and become stonger, then return\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
					}
					else if(charclass[i]!=5)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}

			else if(bsbuy==14)
			{	
				    if (charclass[i]==5)
					{
						system("CLS");
						if(level[i]>=15)
						{
							if(armor[i]==14)
							{
								cout<<"BS: You already have this armor equiped.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(armor[i]>14)
						{
							cout<<"BS: You already have more powerful armor.";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
							else
							{
						
								if(gold<4200)
								{	
									cout<<"BS: You do not have enough gold to purchase that.\n";
									cout<<"BS: You must	slay more enemies in the dungeons.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
								}
								else if(gold>=4200)
								{
									gold=gold-4200;
									cout<<"BS: Thank you for purchasing the Studded Leather,\n";
									cout<<"BS: it shall treat you well on your journey.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
									armor[i]=14;
									statcalc();
								}
							}
						}
						else if(level[i]<15)
						{
							cout<<"BS: You are not able to handle this armor yet.\n";
							cout<<"BS: Slay more enemies and become stonger, then return\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
					}
					else if(charclass[i]!=5)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}


			  i=bschar;


					
		   }
		   while(bsbuy!=0);

	 }



	}
	while (bschoice!=2);
}




void bsTrevia()
{
	do
	{
	   system("CLS");
	   cout<<"  ------------------------\n";
	   cout<<" * Richard the Blacksmith *\n";
	   cout<<"  ------------------------\n";
	   cout<<" Options\n";
	   cout<<"-------------------------\n";
	   cout<<"1.)Buy\n";
	   cout<<"2.)Leave Blacksmith\n";
	   cout<<"-------------------------\n";
	   cout<<"Make your choice: ";
	   cin>>bschoice;

	   

	   
	   if (bschoice==1)
	   {
		   bscharselect();
		   cout<<"Select a Character: ";
		   cin>>bschar;
		   i=bschar;

		   do
		   {
			system("CLS");
			cout<<"  ------------------------      -------------\n";
			cout<<" * Richard the Blacksmith *     Gold: "<<gold<<"\n";
			cout<<"  ------------------------      -------------\n";
			cout<<"   Weapon              Price  |    Armor                Price\n";
			cout<<"-------------------------------------------------------------\n";
			cout<<"1.)Long Sword(F)      1000 G  | 8.)Steel Plate(F)      1300 G\n";
			cout<<"2.)Warhammer(A)        975 G  | 9.)Raw Hide Suit(A)     990 G\n";
			cout<<"3.)Mace(C)             850 G  | 10.)Chain Mail(C)       750 G\n";
			cout<<"4.)Brass Knuckles(M)   800 G  | 11.)Trainer's Suit(M)   880 G\n";
			cout<<"5.)Short Sword(T)      725 G  | 12.)Leather Armor(T)    800 G\n";
			cout<<"6.)Dagger(D)           650 G  | 13.)Mage's Robe(D)     1000 G\n";
			cout<<"7.)Earth Ax(A)*       4800 G  | 14.)Hard Leather(A)*   4300 G\n";
			cout<<"Make your choice(press 0 to return to shop): ";
			cin>>bsbuy;

			bspurchase();
			if(bsbuy==7)
			{	
				    if (charclass[i]==2)
					{
						system("CLS");
						if(level[i]>=15)
						{
							if(weapon[i]==5)
							{
								cout<<"BS: You already have this weapon equiped.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(weapon[i]>5)
						{
							cout<<"BS: You already have a more powerful weapon.";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
							else
							{
						
								if(gold<4800)
								{	
									cout<<"BS: You do not have enough gold to purchase that.\n";
									cout<<"BS: You must	slay more enemies in the dungeons.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
								}
								else if(gold>=4800)
								{
									gold=gold-4800;
									cout<<"BS: Thank you for purchasing the Earth Ax,\n";
									cout<<"BS: it shall treat you well on your journey.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
									weapon[i]=5;
									statcalc();
								}
							}
						}
						else if(level[i]<15)
						{
							cout<<"BS: You are not able to handle this weapon yet.\n";
							cout<<"BS: Slay more enemies and become stonger, then return\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
					}
					else if(charclass[i]!=2)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}

			else if(bsbuy==14)
			{	
				    if (charclass[i]==2)
					{
						system("CLS");
						if(level[i]>=15)
						{
							if(armor[i]==5)
							{
								cout<<"BS: You already have this armor equiped.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(armor[i]>5)
						{
							cout<<"BS: You already have more powerful armor.";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
							else
							{
						
								if(gold<4300)
								{	
									cout<<"BS: You do not have enough gold to purchase that.\n";
									cout<<"BS: You must	slay more enemies in the dungeons.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
								}
								else if(gold>=4300)
								{
									gold=gold-4300;
									cout<<"BS: Thank you for purchasing the Hard Leather,\n";
									cout<<"BS: it shall treat you well on your journey.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
									armor[i]=5;
									statcalc();
								}
							}
						}
						else if(level[i]<15)
						{
							cout<<"BS: You are not able to handle this armor yet.\n";
							cout<<"BS: Slay more enemies and become stonger, then return\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
					}
					else if(charclass[i]!=2)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}


			  i=bschar;


					
		   }
		   while(bsbuy!=0);

	 }



	}
	while (bschoice!=2);
}



void bsRien()
{
	do
	{
	   system("CLS");
	   cout<<"  -----------------------\n";
	   cout<<" * Mortus the Blacksmith *\n";
	   cout<<"  -----------------------\n";
	   cout<<" Options\n";
	   cout<<"-------------------------\n";
	   cout<<"1.)Buy\n";
	   cout<<"2.)Leave Blacksmith\n";
	   cout<<"-------------------------\n";
	   cout<<"Make your choice: ";
	   cin>>bschoice;
	   

	   
	   if (bschoice==1)
	   {
		   bscharselect();
		   cout<<"Select a Character: ";
		   cin>>bschar;
		   i=bschar;

		   do
		   {
			system("CLS");
			cout<<"  -----------------------      -------------\n";
			cout<<" * Mortus the Blacksmith *     Gold: "<<gold<<"\n";
			cout<<"  -----------------------      -------------\n";
			cout<<"   Weapon              Price  |    Armor                 Price\n";
			cout<<"--------------------------------------------------------------\n";
			cout<<"1.)Long Sword(F)      1000 G  | 8.)Steel Plate(F)       1300 G\n";
			cout<<"2.)Warhammer(A)        975 G  | 9.)Raw Hide Suit(A)      990 G\n";
			cout<<"3.)Mace(C)             850 G  | 10.)Chain Mail(C)        750 G\n";
			cout<<"4.)Brass Knuckles(M)   800 G  | 11.)Trainer's Suit(M)    880 G\n";
			cout<<"5.)Short Sword(T)      725 G  | 12.)Leather Armor(T)     800 G\n";
			cout<<"6.)Dagger(D)           650 G  | 13.)Mage's Robe(D)      1000 G\n";
			cout<<"7.)Great Sword(F)*    5200 G  | 14.)Full Plate Mail(F)* 3900 G\n";
			cout<<"Make your choice(press 0 to return to shop): ";
			cin>>bsbuy;

			bspurchase();
			if(bsbuy==7)
			{	
				    if (charclass[i]==1)
					{
						system("CLS");
						if(level[i]>=15)
						{
							if(weapon[i]==2)
							{
								cout<<"BS: You already have this weapon equiped.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(weapon[i]>2)
						{
							cout<<"BS: You already have a more powerful weapon.";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
							else
							{
						
								if(gold<5200)
								{	
									cout<<"BS: You do not have enough gold to purchase that.\n";
									cout<<"BS: You must	slay more enemies in the dungeons.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
								}
								else if(gold>=5200)
								{
									gold=gold-5200;
									cout<<"BS: Thank you for purchasing the Great Sword,\n";
									cout<<"BS: it shall treat you well on your journey.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
									weapon[i]=2;
									statcalc();
								}
							}
						}
						else if(level[i]<15)
						{
							cout<<"BS: You are not able to handle this weapon yet.\n";
							cout<<"BS: Slay more enemies and become stonger, then return\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
					}
					else if(charclass[i]!=1)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}

			else if(bsbuy==14)
			{	
				    if (charclass[i]==1)
					{
						system("CLS");
						if(level[i]>=15)
						{
							if(armor[i]==2)
							{
								cout<<"BS: You already have this armor equiped.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(armor[i]>2)
						{
							cout<<"BS: You already have more powerful armor.";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
							else
							{
						
								if(gold<3900)
								{	
									cout<<"BS: You do not have enough gold to purchase that.\n";
									cout<<"BS: You must	slay more enemies in the dungeons.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
								}
								else if(gold>=3900)
								{
									gold=gold-3900;
									cout<<"BS: Thank you for purchasing the Full Plate Mail,\n";
									cout<<"BS: it shall treat you well on your journey.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
									armor[i]=2;
									statcalc();
								}
							}
						}
						else if(level[i]<15)
						{
							cout<<"BS: You are not able to handle this armor yet.\n";
							cout<<"BS: Slay more enemies and become stonger, then return\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
					}
					else if(charclass[i]!=1)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}


			  i=bschar;


					
		   }
		   while(bsbuy!=0);

	 }



	}
	while (bschoice!=2);
}


void bsBriex()
{
	do
	{
	   system("CLS");
	   cout<<"  ----------------------------\n";
	   cout<<" * Mme Melinda the Blacksmith *\n";
	   cout<<"  ----------------------------\n";
	   cout<<" Options\n";
	   cout<<"-------------------------\n";
	   cout<<"1.)Buy\n";
	   cout<<"2.)Leave Blacksmith\n";
	   cout<<"-------------------------\n";
	   cout<<"Make your choice: ";
	   cin>>bschoice;
	   

	   
	   if (bschoice==1)
	   {
		   bscharselect();
		   cout<<"Select a Character: ";
		   cin>>bschar;
		   i=bschar;

		   do
		   {
			system("CLS");
			cout<<"  ----------------------------      -------------\n";
			cout<<" * Mme Melinda the Blacksmith *     Gold: "<<gold<<"\n";
			cout<<"  ----------------------------      -------------\n";
			cout<<"   Weapon              Price  |    Armor                Price\n";
			cout<<"-------------------------------------------------------------\n";
			cout<<"1.)Long Sword(F)      1000 G  | 8.)Steel Plate(F)      1300 G\n";
			cout<<"2.)Warhammer(A)        975 G  | 9.)Raw Hide Suit(A)     990 G\n";
			cout<<"3.)Mace(C)             850 G  | 10.)Chain Mail(C)       750 G\n";
			cout<<"4.)Brass Knuckles(M)   800 G  | 11.)Trainer's Suit(M)   880 G\n";
			cout<<"5.)Short Sword(T)      725 G  | 12.)Leather Armor(T)    800 G\n";
			cout<<"6.)Dagger(D)           650 G  | 13.)Mage's Robe(D)     1000 G\n";
			cout<<"7.)Morning Star(C)*   4700 G  | 14.)Silver Mail(C)*    5000 G\n";
			cout<<"Make your choice(press 0 to return to shop): ";
			cin>>bsbuy;

			bspurchase();
			if(bsbuy==7)
			{	
				    if (charclass[i]==3)
					{
						system("CLS");
						if(level[i]>=15)
						{
							if(weapon[i]==8)
							{
								cout<<"BS: You already have this weapon equiped.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(weapon[i]>8)
						{
							cout<<"BS: You already have a more powerful weapon.";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
							else
							{
						
								if(gold<4700)
								{	
									cout<<"BS: You do not have enough gold to purchase that.\n";
									cout<<"BS: You must	slay more enemies in the dungeons.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
								}
								else if(gold>=4700)
								{
									gold=gold-4700;
									cout<<"BS: Thank you for purchasing the Morning Star,\n";
									cout<<"BS: it shall treat you well on your journey.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
									weapon[i]=8;
									statcalc();
								}
							}
						}
						else if(level[i]<15)
						{
							cout<<"BS: You are not able to handle this weapon yet.\n";
							cout<<"BS: Slay more enemies and become stonger, then return\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
					}
					else if(charclass[i]!=3)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}

			else if(bsbuy==14)
			{	
				    if (charclass[i]==3)
					{
						system("CLS");
						if(level[i]>=15)
						{
							if(armor[i]==8)
							{
								cout<<"BS: You already have this armor equiped.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(armor[i]>8)
						{
							cout<<"BS: You already have more powerful armor.";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
							else
							{
						
								if(gold<5000)
								{	
									cout<<"BS: You do not have enough gold to purchase that.\n";
									cout<<"BS: You must	slay more enemies in the dungeons.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
								}
								else if(gold>=5000)
								{
									gold=gold-5000;
									cout<<"BS: Thank you for purchasing the Silver Mail,\n";
									cout<<"BS: it shall treat you well on your journey.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
									armor[i]=8;
									statcalc();
								}
							}
						}
						else if(level[i]<15)
						{
							cout<<"BS: You are not able to handle this armor yet.\n";
							cout<<"BS: Slay more enemies and become stonger, then return\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
					}
					else if(charclass[i]!=3)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}


			  i=bschar;


					
		   }
		   while(bsbuy!=0);

	 }



	}
	while (bschoice!=2);
}

void bsUlm()
{
	do
	{
	   system("CLS");
	   cout<<"  ----------------------\n";
	   cout<<" * Karla the Blacksmith *\n";
	   cout<<"  ----------------------\n";
	   cout<<" Options\n";
	   cout<<"-------------------------\n";
	   cout<<"1.)Buy\n";
	   cout<<"2.)Leave Blacksmith\n";
	   cout<<"-------------------------\n";
	   cout<<"Make your choice: ";
	   cin>>bschoice;
	   

	   
	   if (bschoice==1)
	   {
		   bscharselect();
		   cout<<"Select a Character: ";
		   cin>>bschar;
		   i=bschar;

		   do
		   {
			system("CLS");
			cout<<"  ----------------------      -------------\n";
			cout<<" * Karla the Blacksmith *     Gold: "<<gold<<"\n";
			cout<<"  ----------------------      -------------\n";
			cout<<"   Weapon              Price  |    Armor                Price\n";
			cout<<"-------------------------------------------------------------\n";
			cout<<"1.)Long Sword(F)      1000 G  | 8.)Steel Plate(F)      1300 G\n";
			cout<<"2.)Warhammer(A)        975 G  | 9.)Raw Hide Suit(A)     990 G\n";
			cout<<"3.)Mace(C)             850 G  | 10.)Chain Mail(C)       750 G\n";
			cout<<"4.)Brass Knuckles(M)   800 G  | 11.)Trainer's Suit(M)   880 G\n";
			cout<<"5.)Short Sword(T)      725 G  | 12.)Leather Armor(T)    800 G\n";
			cout<<"6.)Dagger(D)           650 G  | 13.)Mage's Robe(D)     1000 G\n";
			cout<<"7.)Nunchaku(M)*       4750 G  | 14.)Ancient Robe(M)*   4950 G\n";
			cout<<"Make your choice(press 0 to return to shop): ";
			cin>>bsbuy;

			bspurchase();
			if(bsbuy==7)
			{	
				    if (charclass[i]==4)
					{
						system("CLS");
						if(level[i]>=15)
						{
							if(weapon[i]==11)
							{
								cout<<"BS: You already have this weapon equiped.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(weapon[i]>11)
						{
							cout<<"BS: You already have a more powerful weapon.";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
							else
							{
						
								if(gold<4750)
								{	
									cout<<"BS: You do not have enough gold to purchase that.\n";
									cout<<"BS: You must	slay more enemies in the dungeons.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
								}
								else if(gold>=4750)
								{
									gold=gold-4750;
									cout<<"BS: Thank you for purchasing the Nunchaku,\n";
									cout<<"BS: it shall treat you well on your journey.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
									weapon[i]=11;
									statcalc();
								}
							}
						}
						else if(level[i]<15)
						{
							cout<<"BS: You are not able to handle this weapon yet.\n";
							cout<<"BS: Slay more enemies and become stonger, then return\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
					}
					else if(charclass[i]!=4)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}

			else if(bsbuy==14)
			{	
				    if (charclass[i]==4)
					{
						system("CLS");
						if(level[i]>=15)
						{
							if(armor[i]==11)
							{
								cout<<"BS: You already have this armor equiped.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(armor[i]>11)
						{
							cout<<"BS: You already have more powerful armor.";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
							else
							{
						
								if(gold<4950)
								{	
									cout<<"BS: You do not have enough gold to purchase that.\n";
									cout<<"BS: You must	slay more enemies in the dungeons.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
								}
								else if(gold>=4950)
								{
									gold=gold-4950;
									cout<<"BS: Thank you for purchasing the Ancient Robe,\n";
									cout<<"BS: it shall treat you well on your journey.\n";
									cout<<"\n";
									cout<<"Press 1 to continue: ";
									cin>>one;
									armor[i]=11;
									statcalc();
								}
							}
						}
						else if(level[i]<15)
						{
							cout<<"BS: You are not able to handle this armor yet.\n";
							cout<<"BS: Slay more enemies and become stonger, then return\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
					}
					else if(charclass[i]!=4)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}


			  i=bschar;


					
		   }
		   while(bsbuy!=0);

	 }



	}
	while (bschoice!=2);
}







































void charcreate()
{
	 do
		{
			system("CLS");
			cout<<"Character Creation #"<<i<<" -Sex\n";
			cout<<"--------------------------\n";
			cout<<"1.)Male\n";
			cout<<"2.)Female\n";
			cout<<"Choice: ";
			cin>>maleorfemale[i];
			system("CLS");
			cout<<"Character Creation #"<<i<<" -Class\n";
			cout<<"----------------------------\n";
			cout<<"1.)Fighter\n";
			cout<<"2.)Acolyte\n";
			cout<<"3.)Cleric\n";
			cout<<"4.)Monk\n";
			cout<<"5.)Thief\n";
			cout<<"6.)Dark Mage\n";
			cout<<"Choice: ";
			cin>>charclass[i];
			system("CLS");
			cout<<"Character Creation #"<<i<<" -Name\n";
			cout<<"---------------------------\n";
			cout<<"Enter your Name: ";
			cin.ignore(81,'\n');
			cin.get(charname[i],21);
			cin.ignore(81,'\n');
			system("CLS");
			cout<<"Character Creation #"<<i<<" -Finalize\n";
			cout<<"-------------------------------\n";
			cout<<"Name: "<<charname[i]<<'\n';
			if(maleorfemale[i]==1)
			{
				cout<<"Sex: Male\n";
			}
			else if(maleorfemale[i]==2)
			{
				cout<<"Sex:Female\n";
			}
				
			cout<<"Class: "<<classname[charclass[i]];
				
			

			level[i]=4;
			xp[i]=600;
			reqxp[i]=1000;
			weapon[i]=0;
			armor[i]=0;
			charnum[i]=1;
			statcalc();
			hp[i]=uchpmax[i];
			mp[i]=ucmpmax[i];
			cout<<"\n";
			cout<<"Press 1 if correct or Press 2 to restart: ";
			cin>>charcorrect;
			system("CLS");
		}
		while(charcorrect!=1);
}

void newgamestory()
{

		gold=5000;
		for(i=0; i<=6; i++)
		{
		progress[i]=0;
		}
		for (i=1; i<=12; i++)
		{
			ditemcheck[i]=1;
			dspecialcheck[i]=1;
		}
		//////START CHARACTER CREATION 1
		i=1;
		charcreate();
		/////////END CHARACTER CREATION 1

		/////////START STORY HERE
		
		cout<<"You wake up in a puddle of you own blood. Your arm is cut and your clothes are\n"
			<<"torn. Where are you? What has happened? You sit up and scan the room. A fire\n"
			<<"is burning in the fireplace and there is a flickering candle on the table.\n"
			<<"How long have you been out for? You hear footsteps coming from around the\n"
			<<"corner. You lay back down, and watch in suspense. A man in a robe walks in with\n"
			<<"a blade in his hand. You close your eyes. He hovers over you waiting for you\n"
			<<"to wake. A knock at the door. He leaves to answer it.\n";
		cout<<"\n";
		cout<<"Press 1 to continue: ";
		cin>>one;
		system("CLS");
		////////BREAK IN STORY 


		///////START CHARACTER CREATION 2
		i=2;
		charcreate();
		////////END CHARACTER CREATION 2

			
			///////CONTINUE STORY
			
		
			cout<<"Man:'Who is it?'\n";
			if (maleorfemale[2]==1)
			{
			cout<<charname[2]<<": 'I am just a lone soldier who has lost his way.'\n";
			}
			else if(maleorfemale[2]==2)
			{
				cout<<charname[2]<<": 'I am just a lone soldier who has lost her way.'\n";
			}
			cout<<charname[2]<<": 'May I come in and warm up?'\n";
			cout<<"Man: 'One minute.'\n";
			cout<<"\n";
			cout<<"The man in the robe turns around to move your body away. He lifts your lifeless\n";
			cout<<"arms and drags you around the corner into the bed room. You can hear the\n";
			cout<<"door open as the lone soldier walks in.\n";
			cout<<"\n";
			cout<<"Press 1 to continue: ";
			cin>>one;
			system("CLS");
			
			cout<<charname[2]<<": 'Thank you so much.'\n";
			cout<<"Man: 'It is no problem for a soldier, fighting for our cause.'\n";
			cout<<"Man: 'Let me get you a blanket.'\n";
			cout<<"\n";
			cout<<"You can hear footsteps as the man turns around to get a blanket out of the room\n";
			cout<<"you are in. Suddenly you hear a struggle, moans, and grunts. On the floor there\n";
			cout<<"is a metal shard; you grab it and attempt to unlock the door to find out what\n";
			cout<<"is happening. The metal shard works as you watch the door slowly open. You peer\n";
			cout<<"around the corner and see the soldier behind the man.\n";
			cout<<"\n";
			
			cout<<charname[2]<<": 'This is for all the ones you have slaughtered.'\n";
			cout<<"\n";
			cout<<"You see the soldier pull a knife from his pocket.\n"; 
			cout<<"\n";
			cout<<charname[2]<<": 'For our country I lay you down!'\n";
			cout<<"\n";
			cout<<"The soldier quickly slits the man's throat and lets him fall to the ground.\n";
			cout<<"\n";
			cout<<"Press 1 to continue: ";
			cin>>one;
			system("CLS");

			cout<<"You come around from the corner.\n";
			cout<<"\n";

			cout<<charname[1]<<": 'Who are you?'\n";
			cout<<charname[2]<<": 'My name is "<<charname[2]<<" a "<<classname[charclass[2]]<<" of Karas. I have come for you.'\n";
			cout<<charname[2]<<": 'When mi'lord, Duke Vlad, heard of your capture he sent me right away.'\n";
 			cout<<charname[1]<<": 'Who was that and why did he capture me?'\n";
			cout<<charname[2]<<": 'You don't know?'\n";
			cout<<charname[1]<<": 'Know what? Tell me now!'\n";
			cout<<charname[2]<<": 'Let me take you to my Lord, he will explain it all to you.'\n";
			cout<<"\n";
			cout<<"Press 1 to go to Karas and start your epic journey: ";
			cin>>one;
			system("CLS");
			/////////////////SEND TO OVERWORLD
}

void karasstory()
{
	system("CLS");
			cout<<"Entering Karas\n";
			cout<<"\n";
			cout<<charname[2]<<": 'We have arrived in beautiful Karas, my hometown.'\n";
			cout<<charname[2]<<": 'Let me take you to mi'lord, Duke Vlad, he will explain everything.'\n";
			cout<<charname[1]<<": 'Alright, let's get this over with.'\n";
			cout<<charname[2]<<": 'Duke Vlad's Castle is right around corner.'\n";
			cout<<"\n";
			cout<<"Walking up to the castle you are stopped by the guards. "<<charname[2]<<" tells\n";
			cout<<"them the story and they escort you into the castle. The castle's halls\n";
			cout<<"are dark and silent. It seems as nothing is moving at all. The guards quickly\n";
			cout<<"take you up the stair case and stop at set of 2 massive doors. They open \n";
			cout<<"the doors and tell you to go in. Walking in you see a man with a large \n";
			cout<<"crown on his head, this must be the Duke. He is clothed in all black,\n";
			cout<<"with a large cain in his hand. He turns around slowly and stares at you\n";
			cout<<"for a moment\n";
			cout<<"\n";
			cout<<"Press 1 to continue: ";
			cin>>one;
			system("CLS");
			cout<<"Duke Vlad: 'Welcome "<<charname[2]<<" I see your journey was successfull.'\n";
			cout<<charname[2]<<": 'Yes it was, I have slain Arthur and returned with "<<charname[1]<<".'\n";
			if(maleorfemale[1]==1)
			{
				cout<<charname[2]<<": 'However he does not have any idea of our current situation.'\n";
			}
			else if(maleorfemale[1]==2)
			{
				cout<<charname[2]<<": 'However she does not have any idea of our current situation.'\n";
			}
			cout<<"\n";
			cout<<"Duke Vlad: '"<<charname[1]<<" let me get you up to speed. After you had slain\n";
			cout<<"the Ancient Dragon, you decided to go on a quest to find out who you \n";
			cout<<"really were. Your beloved Maya tried to stop you, but you needed to know \n";
			cout<<"your past and left her. On you way to Negertia you were ambushed by a\n";
			cout<<"group of rebels. These rebels believed you were part of Saint Williams\n";
			cout<<"army and beat you almost to death. Our intelligents found out that Arthur,\n";
			cout<<"the rebels leader, had taken you to an abandoned cabin between Lille \n";
			cout<<"and Rien. When we heard this news I immediately sent "<<charname[2]<<" to rescue\n";
			cout<<"you, and slay Arthur. As you can see we were sucessfull and you are alive.\n";
			
			cout<<"\n";
			cout<<"Press 1 to continue: ";
			cin>>one;
			system("CLS");
			cout<<charname[1]<<": 'I don't remember any of this, but I thank thee none the less.'\n";
			cout<<charname[2]<<": 'It is important that you understand that they were going to kill you.'\n";
			cout<<"Duke Vlad: 'That is correct, and you are welcome.\n";
			cout<<charname[1]<<": 'I must return to my journey and I must go find Maya she is all\n";
			cout<<"that I have left in this world.\n";
			cout<<"\n";
			cout<<"Duke Vlad: 'I understand your concerns, but we need you now here in Neutria.\n";
			cout<<"Within our country we have 12 sacred dungeons. Deep within the Monument of\n";
			cout<<"Light lies a tomb filled with pure evil. This tomb was closed and sealed shut\n";
			cout<<"with a sacred crest more than 10 thousand years ago. These rebels have\n";
			cout<<"infiltrated the Monument of Light and broken open the crest and  it has\n";
			cout<<"unleashed evil upon our 12 scared dungeons. We have heard of you epic conquest \n";
			cout<<"in East Riverwill, and we need your help now. Will you except this mission\n";
			cout<<"to rid our sacred dungeons of this evil?\n";
			cout<<"\n";
			cout<<"Press 1 to continue: ";
			cin>>one;
			system("CLS");
			cout<<charname[1]<<": 'Let thy deed be done. I have requests however.'\n";
			cout<<"Duke Vlad: 'Of course what will you need?'\n";
			cout<<charname[1]<<": 'First I will need a new set of clothing'\n";
			cout<<charname[1]<<": 'I will also need some gold, and some potions from your shop.'\n";
			cout<<"\n";
			cout<<"Duke Vlad: 'I will prepare it all for you. Thank you so very much. I wish\n";
			cout<<"for you to take "<<charname[2]<<" with you on your journey. Also a third will\n";
			cout<<"join you before you leave the castle. All of Neutria thanks you for your\n";
			cout<<"acceptance of this journey and wish you the best of luck. Return to me when\n";
			cout<<"you have cleared the first dungeon. Good luck.\n";
			cout<<"\n";
			cout<<"Press 1 to leave castle: ";
			cin>>one;
			
			
		/////////////Start Create Character 3	
		i=3;
		charcreate();
		/////////////End Create Character 3
		cremain=3;
		progress[0]=1;	

}

void basesetup()
{
	
	//Read Base Enemy Stats
	ifstream efile;
	efile.open("efile.dat", ios::in);
	for(i = 1; i < 37; i++)
	{
		efile.get(ename[i], 21);
		efile.ignore(80, '\n');
		efile >> behp[i];
		efile >> beatp[i];
		efile >> bedfp[i];
		efile >> bemp[i];
		efile >> bematp[i];
		efile >> bemdfp[i];
		efile >> bespd[i];
		efile.ignore(80, '\n');
	}
	efile.close();

	//Read Base Character Stats
	ifstream cfile;
	cfile.open("cfile.dat", ios::in);
	for(i = 1; i < 19; i++)
	{
		cfile >> bchp[i];
		cfile >> bcatp[i];
		cfile >> bcdfp[i];
		cfile >> bcmap[i];
		cfile >> bcmatp[i];
		cfile >> bcmdfp[i];
		cfile >> bcspd[i];
	}
	cfile.close();
	
}

void loadstats()
{
	cremain = 0;
	//Read User Character Stats
	ifstream charfile;
	charfile.open("charfile.dat", ios::in);
	for(i = 1; i < 4; i++)
	{
		charfile.get(charname[i], 21);
		charfile.ignore(80, '\n');
		charfile >> charclass[i];
		charfile >> hp[i];
		charfile >>	mp[i];
		charfile >> level[i];
		charfile >> xp[i];
		charfile >> reqxp[i];
		charfile >> weapon[i];
		charfile >> armor[i];
		charfile >> maleorfemale[i];
		charfile.ignore(80, '\n');
		if (hp[i]>0)
		{
			cremain=cremain+1;
		}

	}


	charfile.close();

	//Read User Character Stats
	ifstream infile;
	infile.open("motz.dat", ios::in);
	
	infile>>gold;
	infile>>overx;
	infile>>overy;
	for (i=0; i<=6; i++)
	{
	infile>>progress[i];
	}
	infile>>overdirection;
	infile>>towncheck;
	for(i=1; i<=6; i++)
	{
		infile>>key[i];
	}
	for(i = 1; i < 7; i++)
	{
		infile >> itemnum[i];
	}


	infile.close();
	for(i=1; i<4; i++)
	{
		statcalc();
	}

	ifstream dsearch;
	dsearch.open("dsearch.dat", ios::in);
	for (i=1; i<=12; i++)
	{
		dsearch>>ditemcheck[i];
		dsearch>>dspecialcheck[i];
	}
	dsearch.close();

}


void statcalc()
{

	uchpmax[i] = bchp[charclass[i]] * level[i];
	ucatp[i] = bcatp[charclass[i]] * level[i]; 
	ucdfp[i] = bcdfp[charclass[i]] * level[i];
	ucmpmax[i] = bcmap[charclass[i]] * level[i];
	ucmatp[i] = bcmatp[charclass[i]] * level[i];
	ucmdfp[i] = bcmdfp[charclass[i]] * level[i];
	ucspd[i] = bcspd[charclass[i]];
	if((weapon[i] % 3) == 1)
	{
		ueatp[i] = (bcatp[charclass[i]] * 4);
		uematp[i] = (bcmatp[charclass[i]] * 4);
	}
	if((weapon[i] % 3) == 2)
	{
		ueatp[i] = (bcatp[charclass[i]] * 8);
		uematp[i] = (bcmatp[charclass[i]] * 8);
	}
	if(((weapon[i] % 3) == 0) && (weapon[i] != 0))
	{
		ueatp[i] = (bcatp[charclass[i]] * 16);
		uematp[i] = (bcmatp[charclass[i]] * 16);
	}
	if((armor[i] % 3) == 1)
	{
		uedfp[i] = (bcdfp[charclass[i]] * 4);
		uemdfp[i] = (bcmdfp[charclass[i]] * 4);
	}
	if((armor[i] % 3) == 2)
	{
		uedfp[i] = (bcdfp[charclass[i]] * 8);
		uemdfp[i] = (bcmdfp[charclass[i]] * 8);
	}
	if(((armor[i] % 3) == 0) && (armor[i] != 0))
	{
		uedfp[i] = (bcdfp[charclass[i]] * 16);
		uemdfp[i] = (bcmdfp[charclass[i]] * 16);
	}
	
}








void bspurchase()
{

			if(bsbuy==1)
			{	
				    if (charclass[i]==1)
					{
						system("CLS");
						if(weapon[i]==1)
						{
							cout<<"BS: You already have this weapon equiped.\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}

						else if(weapon[i]>1)
						{
							cout<<"BS: You already have a more powerful weapon.\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
					
						
						else
						{
						
							if(gold<1000)
							{	
								cout<<"BS: You do not have enough gold to purchase that.\n";
								cout<<"BS: You must	slay more enemies in the dungeons.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(gold>=1000)
							{
								gold=gold-1000;
								cout<<"BS: Thank you for purchasing the Long Sword,\n";
								cout<<"BS: it shall treat you well on your journey.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
								weapon[i]=1;
								statcalc();
							}
						}
					}
					else if(charclass[i]!=1)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}


			else if(bsbuy==2)
			{	
				    if (charclass[i]==2)
					{
						system("CLS");
						if(weapon[i]==4)
						{
							cout<<"BS: You already have this weapon equiped.\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						else if(weapon[i]>4)
						{
							cout<<"BS: You already have a more powerful weapon.\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
						else
						{
						
							if(gold<975)
							{	
								cout<<"BS: You do not have enough gold to purchase that.\n";
								cout<<"BS: You must	slay more enemies in the dungeons.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(gold>=975)
							{
								gold=gold-975;
								cout<<"BS: Thank you for purchasing the Warhammer,\n";
								cout<<"BS: it shall treat you well on your journey.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
								weapon[i]=4;
								statcalc();
							}
						}
					}
					else if(charclass[i]!=2)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}
			else if(bsbuy==3)
			{	
				    if (charclass[i]==3)
					{
						system("CLS");
						if(weapon[i]==7)
						{
							cout<<"BS: You already have this weapon equiped.\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						else if(weapon[i]>7)
						{
							cout<<"BS: You already have a more powerful weapon.\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
						else
						{
						
							if(gold<850)
							{	
								cout<<"BS: You do not have enough gold to purchase that.\n";
								cout<<"BS: You must	slay more enemies in the dungeons.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(gold>=850)
							{
								gold=gold-850;
								cout<<"BS: Thank you for purchasing the Mace,\n";
								cout<<"BS: it shall treat you well on your journey.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
								weapon[i]=7;
								statcalc();
							}
						}
					}
					else if(charclass[i]!=3)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}

			else if(bsbuy==4)
			{	
				    if (charclass[i]==4)
					{
						system("CLS");
						if(weapon[i]==10)
						{
							cout<<"BS: You already have this weapon equiped.\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						else if(weapon[i]>10)
						{
							cout<<"BS: You already have a more powerful weapon.\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
						else
						{
						
							if(gold<800)
							{	
								cout<<"BS: You do not have enough gold to purchase that.\n";
								cout<<"BS: You must	slay more enemies in the dungeons.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(gold>=800)
							{
								gold=gold-800;
								cout<<"BS: Thank you for purchasing the Brass Knuckles,\n";
								cout<<"BS: it shall treat you well on your journey.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
								weapon[i]=10;
								statcalc();
							}
						}
					}
					else if(charclass[i]!=4)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}


			else if(bsbuy==5)
			{	
				    if (charclass[i]==5)
					{
						system("CLS");
						if(weapon[i]==13)
						{
							cout<<"BS: You already have this weapon equiped.\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						else if(weapon[i]>13)
						{
							cout<<"BS: You already have a more powerful weapon.\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
						else
						{
						
							if(gold<725)
							{	
								cout<<"BS: You do not have enough gold to purchase that.\n";
								cout<<"BS: You must	slay more enemies in the dungeons.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(gold>=725)
							{
								gold=gold-725;
								cout<<"BS: Thank you for purchasing the Short Sword,\n";
								cout<<"BS: it shall treat you well on your journey.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
								weapon[i]=13;
								statcalc();
							}
						}
					}
					else if(charclass[i]!=5)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}


			else if(bsbuy==6)
			{	
				    if (charclass[i]==6)
					{
						system("CLS");
						if(weapon[i]==16)
						{
							cout<<"BS: You already have this weapon equiped.\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						else if(weapon[i]>16)
						{
							cout<<"BS: You already have a more powerful weapon.\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
						else
						{
						
							if(gold<650)
							{	
								cout<<"BS: You do not have enough gold to purchase that.\n";
								cout<<"BS: You must	slay more enemies in the dungeons.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(gold>=650)
							{	
								gold=gold-650;
								cout<<"BS: Thank you for purchasing the Dagger,\n";
								cout<<"BS: it shall treat you well on your journey.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
								weapon[i]=16;
								statcalc();
							}
						}
					}
					else if(charclass[i]!=6)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}



			else if(bsbuy==8)
			{	
				    if (charclass[i]==1)
					{
						system("CLS");
						if(armor[i]==1)
						{
							cout<<"BS: You already have this armor equiped.\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						else if(armor[i]>1)
						{
							cout<<"BS: You already have more powerful armor.";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
						else
						{
						
							if(gold<1300)
							{	
								cout<<"BS: You do not have enough gold to purchase that.\n";
								cout<<"BS: You must	slay more enemies in the dungeons.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(gold>=1300)
							{
								gold=gold-1300;
								cout<<"BS: Thank you for purchasing a Steel Plate,\n";
								cout<<"BS: it shall treat you well on your journey.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
								armor[i]=1;
								statcalc();
							}
						}
					}
					else if(charclass[i]!=1)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}

			else if(bsbuy==9)
			{	
				    if (charclass[i]==2)
					{
						system("CLS");
						if(armor[i]==4)
						{
							cout<<"BS: You already have this armor equiped.\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						else if(armor[i]>4)
						{
							cout<<"BS: You already have more powerful armor.";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
						else
						{
						
							if(gold<990)
							{	
								cout<<"BS: You do not have enough gold to purchase that.\n";
								cout<<"BS: You must	slay more enemies in the dungeons.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(gold>=990)
							{
								gold=gold-990;
								cout<<"BS: Thank you for purchasing a Raw Hide Suit,\n";
								cout<<"BS: it shall treat you well on your journey.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
								armor[i]=4;
								statcalc();
							}
						}
					}
					else if(charclass[i]!=2)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}



			else if(bsbuy==10)
			{	
				    if (charclass[i]==3)
					{
						system("CLS");
						if(armor[i]==7)
						{
							cout<<"BS: You already have this armor equiped.\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						else if(armor[i]>7)
						{
							cout<<"BS: You already have more powerful armor.";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
						else
						{
						
							if(gold<750)
							{	
								cout<<"BS: You do not have enough gold to purchase that.\n";
								cout<<"BS: You must	slay more enemies in the dungeons.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(gold>=750)
							{
								gold=gold-750;
								cout<<"BS: Thank you for purchasing Chain Mail,\n";
								cout<<"BS: it shall treat you well on your journey.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
								armor[i]=7;
								statcalc();
							}
						}
					}
					else if(charclass[i]!=3)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}

			else if(bsbuy==11)
			{	
				    if (charclass[i]==4)
					{
						system("CLS");
						if(armor[i]==10)
						{
							cout<<"BS: You already have this armor equiped.\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						else if(armor[i]>10)
						{
							cout<<"BS: You already have more powerful armor.";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
						else
						{
						
							if(gold<880)
							{	
								cout<<"BS: You do not have enough gold to purchase that.\n";
								cout<<"BS: You must	slay more enemies in the dungeons.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(gold>=880)
							{
								gold=gold-880;
								cout<<"BS: Thank you for purchasing a Trainer's Suite,\n";
								cout<<"BS: it shall treat you well on your journey.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
								armor[i]=10;
								statcalc();
							}
						}
					}
					else if(charclass[i]!=4)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}


			else if(bsbuy==12)
			{	
				    if (charclass[i]==5)
					{
						system("CLS");
						if(armor[i]==13)
						{
							cout<<"BS: You already have this armor equiped.\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						else if(armor[i]>13)
						{
							cout<<"BS: You already have more powerful armor.";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
						else
						{
						
							if(gold<800)
							{	
								cout<<"BS: You do not have enough gold to purchase that.\n";
								cout<<"BS: You must	slay more enemies in the dungeons.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(gold>=800)
							{
								gold=gold-800;
								cout<<"BS: Thank you for purchasing Leather Armor,\n";
								cout<<"BS: it shall treat you well on your journey.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
								armor[i]=13;
								statcalc();
							}
						}
					}
					else if(charclass[i]!=5)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}
			else if(bsbuy==13)
			{	
				    if (charclass[i]==6)
					{
						system("CLS");
						if(armor[i]==16)
						{
							cout<<"BS: You already have this armor equiped.\n";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						else if(armor[i]>16)
						{
							cout<<"BS: You already have more powerful armor.";
							cout<<"\n";
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
						
						else
						{
						
							if(gold<1000)
							{	
								cout<<"BS: You do not have enough gold to purchase that.\n";
								cout<<"BS: You must	slay more enemies in the dungeons.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
							}
							else if(gold>=1000)
							{
								gold=gold-1000;
								cout<<"BS: Thank you for purchasing a Mage's Robe,\n";
								cout<<"BS: it shall treat you well on your journey.\n";
								cout<<"\n";
								cout<<"Press 1 to continue: ";
								cin>>one;
								armor[i]=16;
								statcalc();
							}
						}
					}
					else if(charclass[i]!=6)
					{
						system("CLS");
						cout<<"BS: You can not purchase that item for that class.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
			}

}

void status()
{
	for (i=1; i<=3; i++)
	{
		statcalc();
	}
	system("CLS");
	cout << "Character Stats \n"
	     << setw(14) << "Character: " << setw(21) << charname[1] << setw(21) << charname[2] << setw(21) << charname[3] << '\n'
		 << setw(14) << "Class: " << setw(21) << classname[charclass[1]] << setw(21) << classname[charclass[2]] << setw(21) << classname[charclass[3]] << '\n'
		 << setw(14) << "Gender: " << setw(21) << gender[maleorfemale[1]] << setw(21) << gender[maleorfemale[2]] << setw(21) << gender[maleorfemale[3]] << '\n'
		 << setw(14) << "Level: " << setw(21) << level[1] << setw(21) << level[2] << setw(21) << level[3] << '\n'
		 << setw(14) << "HP: " << setw(17) << hp[1] << "/" << setw(3) << uchpmax[1] << setw(17) << hp[2] << "/" << setw(3) << uchpmax[2] << setw(17) << hp[3] << "/" << setw(3) << uchpmax[3]<< '\n'
		 << setw(14) << "ATP: " << setw(12) << "(" << setw(3) << ((ucatp[1]) + (ueatp[1]) + (atpplus[1])) << setw(1) << ")" << setw(5) << ucatp[1] << setw(12) << "(" << setw(3) << ((ucatp[2]) + (ueatp[2]) + (atpplus[2])) << setw(1) << ")" << setw(5) << ucatp[2] << setw(12) << "(" << setw(3) << ((ucatp[3]) + (ueatp[3]) + (atpplus[3])) << setw(1) << ")" << setw(5)  << ucatp[3] << '\n'
		 << setw(14) << "DFP: " << setw(12) << "(" << setw(3) << ((ucdfp[1]) + (uedfp[1]) + (dfpplus[1]) + (guardplus[1])) << setw(1) << ")" << setw(5) << ucdfp[1] << setw(12) << "(" << setw(3) << ((ucdfp[2]) + (uedfp[2]) + (dfpplus[2]) + (guardplus[2])) << setw(1) << ")" << setw(5) << ucdfp[2] << setw(12) << "(" << setw(3) << ((ucdfp[3]) + (uedfp[3]) + (dfpplus[3]) + (guardplus[3])) << setw(1) << ")" << setw(5)  << ucdfp[3] << '\n'
		 << setw(14) << "MP: " << setw(17) << mp[1] << "/" << setw(3) << ucmpmax[1] << setw(17) << mp[2] << "/" << setw(3) << ucmpmax[2] << setw(17) << mp[3] << "/" << setw(3) << ucmpmax[3]<< '\n'
		 << setw(14) << "MATP: " << setw(12) << "(" << setw(3) << ((ucmatp[1]) + (uematp[1])) << setw(1) << ")" << setw(5) << ucmatp[1] << setw(12) << "(" << setw(3) << ((ucmatp[2]) + (uematp[2])) << setw(1) << ")" << setw(5) << ucmatp[2] << setw(12) << "(" << setw(3) << ((ucmatp[3]) + (uematp[3])) << setw(1) << ")" << setw(5) << ucmatp[3] << '\n'
		 << setw(14) << "MDFP: " << setw(12) << "(" << setw(3) << ((ucmdfp[1]) + (uemdfp[1])) << setw(1) << ")" << setw(5) << ucmdfp[1] << setw(12) << "(" << setw(3) << ((ucmdfp[2]) + (uemdfp[2])) << setw(1) << ")" << setw(5) << ucmdfp[2] << setw(12) << "(" << setw(3) << ((ucmdfp[3]) + (uemdfp[3])) << setw(1) << ")" << setw(5) << ucmdfp[3] << '\n'
		 << setw(14) << "SPD: " << setw(21) << ucspd[1] << setw(21) << ucspd[2] << setw(21) << ucspd[3] << '\n'
		 << setw(14) << "XP: " << setw(21) << xp[1] << setw(21) << xp[2] << setw(21) << xp[3] << '\n'
		 << setw(14) << "ReqXP: " << setw(21) << reqxp[1] << setw(21) << reqxp[2] << setw(21) << reqxp[3] << '\n'
		 << setw(14) << "Weapon: " << setw(21) << weaponname[weapon[1]] << setw(21) << weaponname[weapon[2]] << setw(21) << weaponname[weapon[3]] << '\n'
		 << setw(14) << "Armor: " << setw(21) << armorname[armor[1]] << setw(21) << armorname[armor[2]] << setw(21) << armorname[armor[3]] << '\n'
		 <<"-----------------------------------------------------------------------------\n"
		 << setw(24) << "Party Gold:" << setw(8) << gold << setw(41) << "Keys: \n"
		 << setw(24) << "Healing Potions:" << setw(8) << itemnum[1] << setw(40) << "Hidden Everglades Key: " << key[1] << '\n' 	
		 << setw(24) << "Extra Healing Potions:" << setw(8) << itemnum[2] << setw(40) << "Cavern of the Lost Key: " << key[2] << '\n' 
		 << setw(24) << "Elixirs of Healing:" << setw(8) << itemnum[3] << setw(40) << "Gateway to the Netherworld Key: " << key[3] << '\n' 
	     << setw(24) << "Ether Potions:" << setw(8) << itemnum[4] << setw(40) << "Tomb of Tslor Key: " << key[4] << '\n' 
		 << setw(24) << "Extra Ether Potions:" << setw(8) << itemnum[5] << setw(40) << "Mountainside Key: " << key[5] << '\n' 
		 << setw(24) << "Resurrection Vials:" << setw(8) << itemnum[6] << setw(40) << "Forest of Darkness Key: " << key[6] << '\n'; 
	cout << "Press 1 to continue: ";
	cin >> one;
}

void bscharselect()
{

		   system("CLS");
		   cout<<" ------------------\n";
		   cout<<"* Character Choice *\n";
		   cout<<" ------------------\n";
		   cout<<"1.)"<<charname[1];
		   if((charclass[1]==1) || (charclass[1]==7) || (charclass[1]== 13))
		   {
			   cout<<"(F)\n";
		   }
		   else if((charclass[1]==2)  || (charclass[1]==8) || (charclass[1]== 14))
		   {
			   cout<<"(A)\n";
		   }
		   else if((charclass[1]==3) || (charclass[1]==9) || (charclass[1]== 15))
		   {
			   cout<<"(C)\n";
		   }
		   else if((charclass[1]==4) || (charclass[1]==10) || (charclass[1]== 16))
		   {
			   cout<<"(M)\n";
		   }
		   else if((charclass[1]==5) || (charclass[1]==11) || (charclass[1]== 17))
		   {
			   cout<<"(T)\n";
		   }
		   else if((charclass[1]==6) || (charclass[1]==12) || (charclass[1]== 18))
		   {
			   cout<<"(D)\n";
		   }
		   cout<<"2.)"<<charname[2];
		   if((charclass[2]==1) || (charclass[2]==7) || (charclass[2]== 13))
		   {
			   cout<<"(F)\n";
		   }
		   else if((charclass[2]==2)  || (charclass[2]==8) || (charclass[2]== 14))
		   {
			   cout<<"(A)\n";
		   }
		   else if((charclass[2]==3) || (charclass[2]==9) || (charclass[2]== 15))
		   {
			   cout<<"(C)\n";
		   }
		   else if((charclass[2]==4) || (charclass[2]==10) || (charclass[2]== 16))
		   {
			   cout<<"(M)\n";
		   }
		   else if((charclass[2]==5)  || (charclass[2]==11) || (charclass[2]== 17))
		   {
			   cout<<"(T)\n";
		   }
		   else if((charclass[2]==6) || (charclass[2]==12) || (charclass[2]== 18))
		   {
			   cout<<"(D)\n";
		   }
		   cout<<"3.)"<<charname[3];
		   if((charclass[3]==1)  || (charclass[3]==7) || (charclass[3]== 13))
		   {
			   cout<<"(F)\n";
		   }
		   else if((charclass[3]==2) || (charclass[3]==8) || (charclass[3]== 14))
		   {
			   cout<<"(A)\n";
		   }
		   else if((charclass[3]==3)  || (charclass[3]==9) || (charclass[3]== 15))
		   {
			   cout<<"(C)\n";
		   }
		   else if((charclass[3]==4) || (charclass[3]==10) || (charclass[3]== 16))
		   {
			   cout<<"(M)\n";
		   }
		   else if((charclass[3]==5)  || (charclass[3]==11) || (charclass[3]== 17))
		   {
			   cout<<"(T)\n";
		   }
		   else if((charclass[3]==6)  || (charclass[3]==12) || (charclass[3]== 18))
		   {
			   cout<<"(D)\n";
		   }
		   
}
void dojocharselect()
{

		   system("CLS");
		   
		   cout<<"1.)"<<charname[1];
		   if((charclass[1]==1) || (charclass[1]==7) || (charclass[1]== 13))
		   {
			   cout<<"(F)\n";
		   }
		   else if((charclass[1]==2)  || (charclass[1]==8) || (charclass[1]== 14))
		   {
			   cout<<"(A)\n";
		   }
		   else if((charclass[1]==3) || (charclass[1]==9) || (charclass[1]== 15))
		   {
			   cout<<"(C)\n";
		   }
		   else if((charclass[1]==4) || (charclass[1]==10) || (charclass[1]== 16))
		   {
			   cout<<"(M)\n";
		   }
		   else if((charclass[1]==5) || (charclass[1]==11) || (charclass[1]== 17))
		   {
			   cout<<"(T)\n";
		   }
		   else if((charclass[1]==6) || (charclass[1]==12) || (charclass[1]== 18))
		   {
			   cout<<"(D)\n";
		   }
		   cout<<"2.)"<<charname[2];
		   if((charclass[2]==1) || (charclass[2]==7) || (charclass[2]== 13))
		   {
			   cout<<"(F)\n";
		   }
		   else if((charclass[2]==2)  || (charclass[2]==8) || (charclass[2]== 14))
		   {
			   cout<<"(A)\n";
		   }
		   else if((charclass[2]==3) || (charclass[2]==9) || (charclass[2]== 15))
		   {
			   cout<<"(C)\n";
		   }
		   else if((charclass[2]==4) || (charclass[2]==10) || (charclass[2]== 16))
		   {
			   cout<<"(M)\n";
		   }
		   else if((charclass[2]==5)  || (charclass[2]==11) || (charclass[2]== 17))
		   {
			   cout<<"(T)\n";
		   }
		   else if((charclass[2]==6) || (charclass[2]==12) || (charclass[2]== 18))
		   {
			   cout<<"(D)\n";
		   }
		   cout<<"3.)"<<charname[3];
		   if((charclass[3]==1)  || (charclass[3]==7) || (charclass[3]== 13))
		   {
			   cout<<"(F)\n";
		   }
		   else if((charclass[3]==2) || (charclass[3]==8) || (charclass[3]== 14))
		   {
			   cout<<"(A)\n";
		   }
		   else if((charclass[3]==3)  || (charclass[3]==9) || (charclass[3]== 15))
		   {
			   cout<<"(C)\n";
		   }
		   else if((charclass[3]==4) || (charclass[3]==10) || (charclass[3]== 16))
		   {
			   cout<<"(M)\n";
		   }
		   else if((charclass[3]==5)  || (charclass[3]==11) || (charclass[3]== 17))
		   {
			   cout<<"(T)\n";
		   }
		   else if((charclass[3]==6)  || (charclass[3]==12) || (charclass[3]== 18))
		   {
			   cout<<"(D)\n";
		   }

		   
}

void battle()
{
	gainedxp = 0;
	gainedgold = 0;
	runindicator = 0;
	//Regular Battle
	if(bosscheck == 0)
	{
		egenerator();
	}
	//Boss Battle
	else
	{
		bgenerator();
	}
	sgenerator();
	//Battle
	do
	{
		//Battle Sequence
		for(i = 1; i <= enemycount; i++)
		{
			//Player Turn
			if(((sequence[i] >= 1) && (sequence[i] <= 3)) && ((hp[sequence[i]]) > 0))
			{
				turn = 0;
				//Stat Bonus Effect Duration
				if(atpduration[sequence[i]] > 0)
				{
					atpduration[sequence[i]] = atpduration[sequence[i]] - 1;
				}
				if(atpduration[sequence[i]] == 0)
				{
					atpplus[sequence[i]] = 0;
				}
				if(dfpduration[sequence[i]] > 0)
				{
					dfpduration[sequence[i]] = dfpduration[sequence[i]] - 1;
				}
				if(dfpduration[sequence[i]] == 0)
				{
					dfpplus[sequence[i]] = 0;
				}
				if(guardduration[sequence[i]] > 0)
				{
					guardduration[sequence[i]] = guardduration[sequence[i]] - 1;
				}
				if(guardduration[sequence[i]] == 0)
				{
					guardplus[sequence[i]] = 0;
				}
				do
				{
					system("CLS");
					battlescreen();
					cout << "Options \n"
						 << "------------------\n"
						 << "1) Attack \n"
						 << "2) Use Magic \n"
						 << "3) Use Items \n"
						 << "4) Defend \n"
						 << "5) View Statistics \n"
						 << "6) Run \n"
						 << "Enter an action for " << charname[sequence[i]] << ": ";
					do
					{
						cin >> battleoption;
					}
					while((battleoption < 1) || (battleoption > 6));
					system("CLS");
					battlescreen();
					switch(battleoption)
					{
					case 1:
						//Attack
						cout << "Select a Target: \n"
							 << "0) Cancel \n"
							 << "1) " << tename[4] << '\n'
							 << "2) " << tename[5] << '\n'
							 << "3) " << tename[6] << '\n';
						do
						{
							cin >> target;
						}
						while((((target < 1) || (target > 3)) || (tehp[target + 3] == 0)) && (target != 0));
						if(target != 0)
						{
							turn = 1;
							target = target + 3;
							x = (rand() % 20) + 1;
							if(x > tespd[target])
							{
								damage = ((ucatp[sequence[i]]) + (ueatp[sequence[i]]) + (atpplus[sequence[i]])) - ((tedfp[target]) / 2);
								if(damage < 0)
								{
									damage = 0;
								}
								tehp[target] = tehp[target] - damage;
								cout << charname[sequence[i]] << " attacks and inflicts " << damage << " damage to " << tename[target] << ". \n";
								if(tehp[target] <= 0)
								{
									edeath();
								}
							}
							else
							{
								cout << charname[sequence[i]] << " attacks. " << tename[target] << " quickly evades the attack. \n";
							}
						}
						else
						{
							turn = 0;
						}
						break;
					case 2:
						//Magic Use
						magicuse();
						if(spellnum != 0)
						{
							system("CLS");
							battlescreen();
							cout << "Select a Target: \n";
							if(((spellnum % 8) == 1) || ((spellnum % 8) == 3) || ((spellnum % 8) == 4) || ((spellnum % 8) == 7))
							{
								cout << "1) " << charname[1] << '\n'
									 << "2) " << charname[2] << '\n'
									 << "3) " << charname[3] << '\n';
								do
								{
									cin >> target;
								}
								while(((target < 1) || (target > 3)));
							}
							else
							{
								cout << "1) " << tename[4] << '\n'
									 << "2) " << tename[5] << '\n'
									 << "3) " << tename[6] << '\n';
								do
								{
									cin >> target;
								}
								while(((target < 1) || (target > 3)) || ((tehp[target + 3]) == 0));
								target = target + 3;
							}
							spelleffect();
						}
						break;
					case 3:
						//Item Use
						itemuse();
						break;
					case 4:
						//Defend
						guardplus[sequence[i]] = ucdfp[sequence[i]] * .1;
						guardduration[sequence[i]] = 1;
						cout << charname[sequence[i]] << " takes a defensive stance. \n";
						turn = 1;
						break;
					case 5:
						//View Statistics
						cout << "Press 1 to continue: ";
						cin >> one;
						status();
						estatus();
						turn = 0;
						break;
					case 6:
						//Run
						cout << "The party attempts to flee... \n";
						turn = 1;
						//Boss Battle (can't run)
						if(bosscheck == 1)
						{
							cout << "... but they are blocked by the enemies! \n";
							runindicator = 0;
						}
						//Regular Battle
						else
						{
							x = rand() % 2;
							if(x == 0)
							{
								//run indicator
								runindicator = 1;
								//for-loop forced end
								i = enemycount + 2;
								//do-loop forced end
								eremain = 0;
								cout << "... and they manage to escape. \n";								
							}
							else
							{
								runindicator = 0;
								cout << "... but they are blocked by the enemies! \n";
							}
						}
						break;
					default:
						break;
					}
					cout << "Press 1 to continue \n";
					cin >> one;
				}
				while(turn != 1);
			}
			//Enemy Turn
			else if(((sequence[i] >= 4) && (sequence[i] <= enemycount)) && ((tehp[sequence[i]]) > 0))
			{
				battlescreen();
				do
				{
					x = (rand() % 12) + 1;
					if(((x >= 1) && (x <= 5)) && (hp[1] > 0))
					{
						target = 1;
					}
					else if(((x >=6) && (x <= 9)) && (hp[2] > 0))
					{
						target = 2;
					}
					else if((x > 9) && (hp[3] > 0))
					{
						target = 3;
					}
					else
					{
						target = 0;
					}
				}
				while(target == 0);
				//Enemy action randomizer
				x = rand() % 3;
				if((temp[sequence[i]] == 0) || (x == 0))
				{
					//Enemy Attack
					x = (rand() % 20) + 1;
					if(x > ucspd[target])
					{
						damage = (teatp[sequence[i]]) - (((ucdfp[target]) + (uedfp[target]) + (dfpplus[target]) + (guardplus[target])) / 2);
						if(damage < 0)
						{
							damage = 0;
						}
						hp[target] = hp[target] - damage;
						cout << tename[sequence[i]] << " attacks. It inflicts " << damage << " damage to " << charname[target] << ". \n";
						if(hp[target] <= 0)
						{
							cout << charname[target] << " is slain. \n";
							hp[target] = 0;
							cremain = cremain - 1;
							if(cremain == 0)
							{
								//for-loop forced end
								i = enemycount + 2;
							}
						}
					}
					else
					{
						cout << tename[sequence[i]] << " attacks. " << charname[target] << " quickly evades the attack. \n";
					}
				}
				else
				{
					//Enemy Magic
					emagic();
				}
				cout << "Press 1 to continue \n";
				cin >> one;
			}	
		}
	}
	while((eremain != 0) && (cremain != 0));
	
	//End of Battle Messages
	system("CLS");
	//Victory boss check to reset dspecial
	if((eremain == 0) && (bosscheck == 1))
	{
		dspecialcheck[dungeonnum] = 0;
		progress[(dungeonnum / 2)] = 1;
	}
	//Bosscheck Reset
	bosscheck = 0;
	//Reset Modified Stats and Durations
	for(i = 1; i < 4; i++)
	{
		atpduration[i] = 0;
		atpplus[i] = 0;
		dfpduration[i] = 0;
		dfpplus[i] = 0;
		guardduration[i] = 0;
		guardplus[i] = 0;
	}
	if(eremain == 0)
	{
		if(runindicator != 1)
		{
			cout << "The party is victorious! \n";
			cout << "The party has gained " << gainedxp << " experience points and " << gainedgold << " gold. \n";
			for(i = 1; i < 4; i++)
			{
				if(hp[i] != 0)
				{
					xp[i] = xp[i] + (gainedxp / cremain);
				}
				if(xp[i] >= reqxp[i])
				{
					cout << charname[i] << " has gained a level! \n";
					level[i] = level[i] + 1;
					reqxp[i] = reqxp[i] + (level[i] * 100);
					//Recalculate Stats at next level
					statcalc();
				}
			}
			gold = gold + gainedgold;
			cout << "Press one to continue \n";
			cin >> one;
		}
	}
	else if(cremain == 0)
	{
		cout << "The party has been defeated. \n";
		cout << "Game Over \n";
		townpick = 10;
		overcheck = 1;
		dungeonchoice = 3;
		dexitcheck = 1;
		cout << "Press one to continue \n";
		cin >> one;
	}				
}

void battlescreen()
{
	system("CLS");
	//Party
	cout << "-------------------------------------------------------------------------------\n"
	     << "|" << setw(12) << "Character: " << setw(21) << charname[1] << setw(21) << charname[2] << setw(21) << charname[3] << setw(3) << "|" << '\n'
		 << "|" << setw(12) << "HP: " << setw(17) << hp[1] << "/" << setw(3) << uchpmax[1] << setw(17) << hp[2] << "/" << setw(3) << uchpmax[2] << setw(17) << hp[3] << "/" << setw(3) << uchpmax[3]<< setw(3) << "|" << '\n'
		 << "|" << setw(12) << "MP: " << setw(17) << mp[1] << "/" << setw(3) << ucmpmax[1] << setw(17) << mp[2] << "/" << setw(3) << ucmpmax[2] << setw(17) << mp[3] << "/" << setw(3) << ucmpmax[3]<< setw(3) << "|" << '\n'
		 << "-------------------------------------------------------------------------------\n";
	//Enemies
	cout << "|" << setw(12) << "Enemy: " << setw(21) << tename[4] << setw(21) << tename[5] << setw(21) << tename[6] << setw(3) << "|" << '\n'
		 << "|" << setw(12) << "HP: " << setw(17) << tehp[4] << "/" << setw(3) << tehpmax[4] << setw(17) << tehp[5] << "/" << setw(3) << tehpmax[5] << setw(17) << tehp[6] << "/" << setw(3) << tehpmax[6]<< setw(3) << "|" << '\n'
		 << "|" << setw(12) << "MP: " << setw(17) << temp[4] << "/" << setw(3) << tempmax[4] << setw(17) << temp[5] << "/" << setw(3) << tempmax[5] << setw(17) << temp[6] << "/" << setw(3) << tempmax[6]<< setw(3) << "|" << '\n'
		 << "-------------------------------------------------------------------------------\n";
}

void estatus()
{
	system("CLS");
	cout << "Monster Statistics \n"
	     << setw(14) << "Enemy: " << setw(21) << tename[4] << setw(21) << tename[5] << setw(21) << tename[6] << '\n'
		 << setw(14) << "Level: " << setw(21) << televel[4] << setw(21) << televel[5] << setw(21) << televel[6] << '\n'
		 << setw(14) << "HP: " << setw(17) << tehp[4] << "/" << setw(3) << tehpmax[4] << setw(17) << tehp[5] << "/" << setw(3) << tehpmax[5] << setw(17) << tehp[6] << "/" << setw(3) << tehpmax[6]<< '\n'
		 << setw(14) << "ATP: " << setw(21) << teatp[4] << setw(21) << teatp[5] << setw(21) << teatp[6] << '\n'
		 << setw(14) << "DFP: " << setw(21) << tedfp[4] << setw(21) << tedfp[5] << setw(21) << tedfp[6] << '\n'
		 << setw(14) << "MP: " << setw(17) << temp[4] << "/" << setw(3) << tempmax[4] << setw(17) << temp[5] << "/" << setw(3) << tempmax[5] << setw(17) << temp[6] << "/" << setw(3) << tempmax[6]<< '\n'
		 << setw(14) << "MATP: " << setw(21) << tematp[4] << setw(21) << tematp[5] << setw(21) << tematp[6] << '\n'
		 << setw(14) << "MDFP: " << setw(21) << temdfp[4] << setw(21) << temdfp[5] << setw(21) << temdfp[6] << '\n'
		 << setw(14) << "SPD: " << setw(21) << tespd[4] << setw(21) << tespd[5] << setw(21) << tespd[6] << '\n'
		 << '\n';
}

void egenerator()
{
	//New variables for egenerator
	
	//Generate Number of Enemies (1 - 3)
	enemycount = (rand() % 3) + 4;
	eremain = enemycount - 3;
	//Generate Temporary Enemy Stats
	for(j = 4; j <= enemycount; j++)
	{
		z = (dungeonnum * 3) - (rand() % 3);
		televel[j] = ((level[1] + level[2] + level[3]) / 3) + ((rand() % 3) - 1);
		if(televel[j] == 0)
		{
			televel[j] = 1;
		}
		strcpy_s(tename[j], ename[z]);
		tehpmax[j] = behp[z] * televel[j];
		teatp[j] = beatp[z] * televel[j];
		tedfp[j] = bedfp[z] * televel[j];
		tempmax[j] = bemp[z] * televel[j];
		tematp[j] = bematp[z] * televel[j];
		temdfp[j] = bemdfp[z] * televel[j];
		tespd[j] = bespd[z];
		tehp[j] = tehpmax[j];
		temp[j] = tempmax[j];
	}
	for(l = (enemycount + 1); l < 7; l++)
	{
		strcpy_s(tename[l], "");
		televel[l] = 0;
		tehpmax[l] = 0;
		teatp[l] = 0;
		tedfp[l] = 0;
		tempmax[l] = 0;
		tematp[l] = 0;
		temdfp[l] = 0;
		tespd[l] = 0;
		tehp[l] = tehpmax[l];
		temp[l] = tempmax[l];
	}
}

void bgenerator()
{
	//New variables for bgenerator
	int k, n;
	//Generate Number of Enemies (1 - 3)
	enemycount = 6;
	eremain = enemycount - 3;
	//Generate Temporary Boss Enemy Stats
	//Dungeonnum	2  4  6  8 10 12
	//Boss Num		1  2  3  4  5  6
	strcpy_s(tename[4], bossname[(dungeonnum / 2)]);
	televel[4] = ((level[1] + level[2] + level[3]) / 3) + ((rand() % 3) + 1);
	if(televel[4] == 0)
	{
		televel[4] = 1;
	}
	tehpmax[4] = bosshp[(dungeonnum / 2)] * televel[4];
	teatp[4] = bossatp[(dungeonnum / 2)] * televel[4];
	tedfp[4] = bossdfp[(dungeonnum / 2)] * televel[4];
	tempmax[4] = bossmp[(dungeonnum / 2)] * televel[4];
	tematp[4] = bossmatp[(dungeonnum / 2)] * televel[4];
	temdfp[4] = bossmdfp[(dungeonnum / 2)] * televel[4];
	tespd[4] = bossspd[(dungeonnum / 2)];
	tehp[4] = tehpmax[4];
	temp[4] = tempmax[4];
	//Generate Temporary Regular Enemy Stats
	for(k = 5; k <= enemycount; k++)
	{
		n = (dungeonnum * 3) - (rand() % 3);
		televel[k] = ((level[1] + level[2] + level[3]) / 3) + ((rand() % 3) - 1);
		if(televel[k] == 0)
		{
			televel[k] = 1;
		}
		strcpy_s(tename[k], ename[n]);
		tehpmax[k] = behp[n] * televel[k];
		teatp[k] = beatp[n] * televel[k];
		tedfp[k] = bedfp[n] * televel[k];
		tempmax[k] = bemp[n] * televel[k];
		tematp[k] = bematp[n] * televel[k];
		temdfp[k] = bemdfp[n] * televel[k];
		tespd[k] = bespd[n];
		tehp[k] = tehpmax[k];
		temp[k] = tempmax[k];
	}
}

void sgenerator()
{
	//Sequences
	//1 = Character 1
	//2 = Character 2
	//3 = Character 3
	//4 = Enemy 1
	//5 = Enemy 2
	//6 = Enemy 3
	counter = enemycount;
	for(i = 1; i <= 3; i++)
	{
		sequence[i] = i;
		speedcalc[i] = ucspd[i];
	}
	for(i = 4; i <= counter; i++)
	{
		sequence[i] = i;
		speedcalc[i] = tespd[i];
	}
	//Sort by Speed
	do
	{
		for(i = 1; i < counter; i++)
		{
			if(speedcalc[i] < speedcalc[i + 1])
			{
				tempsequence = sequence[i];
				tempspeedcalc = speedcalc[i];
				sequence[i] = sequence[i + 1];
				speedcalc[i] = speedcalc[i + 1];
				sequence[i + 1] = tempsequence;
				speedcalc[i + 1] = tempspeedcalc;
			}
		}
		counter = counter - 1;
	}
	while(counter >= 0);
}

void magicuse()
{
	//Magic Use
	cout << "Select the magic spell you wish to cast: \n";
	turn = 1;
	//White Magic
	if((charclass[sequence[i]]) == 13)
	{
		cout << " 0.) Cancel \n"
			 << " 1.) Heal I       3 MP \n"
			 << " 2.) Light I      4 MP \n";
		do
		{
			cin >> spellchoice;
		}
		while((spellchoice < 0) || (spellchoice > 2));
		if(spellchoice == 1)
		{
			spellnum = 1;
		}
		else if(spellchoice == 2)
		{
			spellnum = 2;
		}
		else
		{
			spellnum = 0;
			turn = 0;
		}
	}
	else if(((charclass[sequence[i]]) == 8) || ((charclass[sequence[i]]) == 14))
	{
		cout << " 0.) Cancel \n"
			 << " 1.) Heal I          3 MP \n"
			 << " 2.) Light I         4 MP \n"
			 << " 3.) DFPUP I         3 MP \n";
		if((charclass[sequence[i]]) == 14)
		{
			cout << " 4.) Heal II         6 MP \n"
				 << " 5.) Light II        8 MP \n"
				 << " 6.) DFPUP II        6 MP \n";
		}
		do
		{
			cin >> spellchoice;
		}
		while((spellchoice < 0) || (spellchoice > 6));
		if(spellchoice == 1)
		{
			spellnum = 1;
		}
		else if(spellchoice == 2)
		{
			spellnum = 2;
		}
		else if(spellchoice == 3)
		{
			spellnum = 3;
		}
		else if(spellchoice == 4)
		{
			if((charclass[sequence[i]]) == 14)
			{
				spellnum = 9;
			}
			else
			{
				spellnum = 1;
			}
		}
		else if(spellchoice == 5)
		{
			if((charclass[sequence[i]]) == 14)
			{
				spellnum = 10;
			}
			else
			{
				spellnum = 2;
			}
		}
		else if(spellchoice == 6)
		{
			if((charclass[sequence[i]]) == 14)
			{
				spellnum = 11;
			}
			else
			{
				spellnum = 3;
			}
		}
		else
		{
			spellnum = 0;
			turn = 0;
		}
	}
	else if(((charclass[sequence[i]]) == 3) || ((charclass[sequence[i]]) == 9) || ((charclass[sequence[i]]) == 15))
	{
		cout << " 0.) Cancel \n"
			 << " 1.) Heal I          3 MP \n"
			 << " 2.) Light I         4 MP \n"
			 << " 3.) DFPUP I         3 MP \n"
			 << " 4.) Resurrect I " << setw(10) << "20 MP \n";
		if(((charclass[sequence[i]]) == 9) || ((charclass[sequence[i]]) == 15))
		{
			cout << " 5.) Heal II         6 MP \n"
				 << " 6.) Light II        8 MP \n"
				 << " 7.) DFPUP II        6 MP \n"
				 << " 8.) Resurrect II   30 MP \n";
		}
		if((charclass[sequence[i]]) == 15)
		{
			cout << " 9.) Heal III       12 MP \n"
				 << "10.) Light III      16 MP \n"
				 << "11.) DFPUP III      10 MP \n"
				 << "12.) Resurrect III  40 MP \n";
		}
		do
		{
			cin >> spellchoice;
		}
		while((spellchoice < 0) || (spellchoice > 12));
		if(spellchoice == 1)
		{
			spellnum = 1;
		}
		else if(spellchoice == 2)
		{
			spellnum = 2;
		}
		else if(spellchoice == 3)
		{
			spellnum = 3;
		}
		else if(spellchoice == 4)
		{
			spellnum = 4;
		}
		else if(spellchoice == 5)
		{
			if(((charclass[sequence[i]]) == 9) || ((charclass[sequence[i]]) == 15))
			{
				spellnum = 9;
			}
			else
			{
				spellnum = 1;
			}
		}
		else if(spellchoice == 6)
		{
			if(((charclass[sequence[i]]) == 9) || ((charclass[sequence[i]]) == 15))
			{
				spellnum = 10;
			}
			else
			{
				spellnum = 2;
			}
		}
		else if(spellchoice == 7)
		{
			if(((charclass[sequence[i]]) == 9) || ((charclass[sequence[i]]) == 15))
			{
				spellnum = 11;
			}
			else
			{
				spellnum = 3;
			}
		}	
		else if(spellchoice == 8)
		{
			if(((charclass[sequence[i]]) == 9) || ((charclass[sequence[i]]) == 15))
			{
				spellnum = 12;
			}
			else
			{
				spellnum = 4;
			}
		}
		else if(spellchoice == 9)
		{
			if((charclass[sequence[i]]) == 15)
			{
				spellnum = 17;
			}
			else
			{
				spellnum = 1;
			}
		}
		else if(spellchoice == 10)
		{
			if((charclass[sequence[i]]) == 15)
			{
				spellnum = 18;
			}
			else
			{
				spellnum = 2;
			}
		}
		else if(spellchoice == 11)
		{
			if((charclass[sequence[i]]) == 15)
			{
				spellnum = 19;
			}
			else
			{
				spellnum = 3;
			}
		}
		else if(spellchoice == 12)
		{
			if((charclass[sequence[i]]) == 15)
			{
				spellnum = 20;
			}
			else
			{
				spellnum = 4;
			}
		}
		else
		{
			spellnum = 0;
			turn = 0;
		}
	}
	//Black Magic
	else if((charclass[sequence[i]]) == 16)
	{
		cout << " 0.) Cancel \n"
			 << " 1.) Fire I          2 MP \n"
			 << " 2.) Ice I           3 MP \n";
		do
		{
			cin >> spellchoice;
		}
		while((spellchoice < 0) || (spellchoice > 2));
		if(spellchoice == 1)
		{
			spellnum = 5;
		}
		else if(spellchoice == 2)
		{
			spellnum = 6;
		}						
		else
		{
			spellnum = 0;
			turn = 0;
		}
	}
	else if(((charclass[sequence[i]]) == 11) || ((charclass[sequence[i]]) == 17))
	{
		cout << " 0.) Cancel \n"
			 << " 1.) Fire I          2 MP \n"
			 << " 2.) Ice I           3 MP \n"
			 << " 3.) ATPUP I         3 MP \n";
		if((charclass[sequence[i]]) == 17)
		{
			cout << " 4.) Fire II        5 MP \n"
				 << " 5.) Ice II         6 MP \n"
				 << " 6.) ATPUP II       6 MP \n";
		}
		do
		{
			cin >> spellchoice;
		}
		while((spellchoice < 0) || (spellchoice > 6));
		if(spellchoice == 1)
		{
			spellnum = 5;
		}
		else if(spellchoice == 2)
		{
			spellnum = 6;
		}
		else if(spellchoice == 3)
		{
			spellnum = 7;
		}
		else if(spellchoice == 4)
		{
			if((charclass[sequence[i]]) == 17)
			{
				spellnum = 13;
			}
			else
			{
				spellnum = 5;
			}
		}
		else if(spellchoice == 5)
		{
			if((charclass[sequence[i]]) == 17)
			{
				spellnum = 14;
			}
			else
			{
				spellnum = 6;
			}
		}
		else if(spellchoice == 6)
		{
			if((charclass[sequence[i]]) == 17)
			{
				spellnum = 15;
			}
			else
			{
				spellnum = 7;
			}
		}
		else
		{
			spellnum = 0;
			turn = 0;
		}
	}
	else if(((charclass[sequence[i]]) == 6) || ((charclass[sequence[i]]) == 12) || ((charclass[sequence[i]]) == 18))
	{
		cout << " 0.) Cancel \n"
			 << " 1.) Fire I          2 MP \n"
			 << " 2.) Ice I           3 MP \n"
			 << " 3.) ATPUP I         3 MP \n"
			 << " 4.) Black Hole I   10 MP \n";
		if(((charclass[sequence[i]]) == 12) || ((charclass[sequence[i]]) == 18))
		{
			cout << " 5.) Fire II         5 MP \n"
				 << " 6.) Ice II          6 MP \n"
				 << " 7.) ATPUP II        6 MP \n"
				 << " 8.) Black Hole II  15 MP \n";
		}			   
		if((charclass[sequence[i]]) == 18)
		{
			cout << " 9.) Fire III       10 MP \n"
				 << "10.) Ice III        12 MP \n"
				 << "11.) ATPUP III      10 MP \n"
				 << "12.) Black Hole III 25 MP \n";
		}
		do
		{
			cin >> spellchoice;
		}
		while((spellchoice < 0) || (spellchoice > 12));
		if(spellchoice == 1)
		{
			spellnum = 5;
		}
		else if(spellchoice == 2)
		{
			spellnum = 6;
		}
		else if(spellchoice == 3)
		{
			spellnum = 7;
		}
		else if(spellchoice == 4)
		{
			spellnum = 8;
		}
		else if(spellchoice == 5)
		{
			if(((charclass[sequence[i]]) == 12) || ((charclass[sequence[i]]) == 18))
			{
				spellnum = 13;
			}
			else
			{
				spellnum = 5;
			}
		}
		else if(spellchoice == 6)
		{
			if(((charclass[sequence[i]]) == 12) || ((charclass[sequence[i]]) == 18))
			{
				spellnum = 14;
			}
			else
			{
				spellnum = 6;
			}
		}
		else if(spellchoice == 7)
		{
			if(((charclass[sequence[i]]) == 12) || ((charclass[sequence[i]]) == 18))
			{
				spellnum = 15;
			}
			else
			{
				spellnum = 7;
			}
		}	
		else if(spellchoice == 8)
		{
			if(((charclass[sequence[i]]) == 12) || ((charclass[sequence[i]]) == 18))
			{
				spellnum = 16;
			}
			else
			{
				spellnum = 8;
			}
		}
		else if(spellchoice == 9)
		{
			if((charclass[sequence[i]]) == 18)
			{
				spellnum = 21;
			}
			else
			{
				spellnum = 5;
			}
		}
		else if(spellchoice == 10)
		{
			if((charclass[sequence[i]]) == 18)
			{
				spellnum = 22;
			}
			else
			{
				spellnum = 6;
			}
		}
		else if(spellchoice == 11)
		{
			if((charclass[sequence[i]]) == 18)
			{
				spellnum = 23;
			}
			else
			{
				spellnum = 7;
			}
		}
		else if(spellchoice == 12)
		{
			if((charclass[sequence[i]]) == 18)
			{
				spellnum = 24;
			}
			else
			{
				spellnum = 8;
			}
		}
		else
		{
			spellnum = 0;
			turn = 0;
		}
	}
	else
	{
		cout << "You are unable to use magic. \n";
		turn = 0;
		spellchoice = 0;
		spellnum = 0;
	}
}

void spelleffect()
{
	system("CLS");
	battlescreen();
	//Level I Spells	
	//Heal I
	if((spellnum == 1) && ((mp[sequence[i]]) >= 3))
	{
		if(hp[target] != 0)
		{
			damage = (((ucmatp[sequence[i]]) + (uematp[sequence[i]])) * .75);
			hp[target] = hp[target] + damage;
			mp[sequence[i]] = mp[sequence[i]] - 3;
			if((hp[target]) > (uchpmax[target]))
			{
				hp[target] = uchpmax[target];
			}
			cout << charname[sequence[i]] << " casts Heal I. " << charname[target] << " is healed for " << damage << " HP. \n";	
		}
		else
		{
			cout << charname[target] << " is dead! \n";
			turn = 0;
		}
	}
	//Light I
	else if((spellnum == 2) && ((mp[sequence[i]]) >= 4))
	{
		damage = ((((ucmatp[sequence[i]]) + (uematp[sequence[i]])) * .75) - ((temdfp[target]) / 2));
		if(damage < 0)
		{
			damage = 0;
		}
		tehp[target] = tehp[target] - damage;
		mp[sequence[i]] = mp[sequence[i]] - 4;
		cout << charname[sequence[i]] << " casts Light I. " << tename[target] << " is damaged for " << damage << " HP. \n";
		if((tehp[target]) < 0)
		{
			edeath();
		}	
	}
	//DFPUP I
	else if((spellnum == 3) && ((mp[sequence[i]]) >= 3))
	{
		dfpplus[target] = 10;
		dfpduration[target] = 2;
		mp[sequence[i]] = mp[sequence[i]] - 3;
		cout << charname[sequence[i]] << " casts DFPUP I. " << charname[target] << "'s defense increases. \n";	
	}
	//Resurrect I
	else if((spellnum == 4) && ((mp[sequence[i]]) >= 20))
	{
		if(hp[target] == 0)
		{
			hp[target] = 1;
			mp[sequence[i]] = mp[sequence[i]] - 20;
			cremain = cremain + 1;
			cout << charname[sequence[i]] << " casts Resurrect I. " << charname[target] << " is revived. \n";
		}
		else
		{
			cout << charname[target] << " is not dead! \n";
			turn = 0;
		}
	}
	//Fire I
	else if((spellnum == 5) && ((mp[sequence[i]]) >= 2))
	{
		damage = ((((ucmatp[sequence[i]]) + (uematp[sequence[i]])) * .5) - ((temdfp[target]) / 2));
		if(damage < 0)
		{
			damage = 0;
		}
		tehp[target] = tehp[target] - damage;
		mp[sequence[i]] = mp[sequence[i]] - 2;
		cout << charname[sequence[i]] << " casts Fire I. " << tename[target] << " is damaged for " << damage << " HP. \n";
		if((tehp[target]) < 0)
		{
			edeath();
		}		
	}
	//Ice I
	else if((spellnum == 6) && ((mp[sequence[i]]) >= 3))
	{
		damage = ((((ucmatp[sequence[i]]) + (uematp[sequence[i]])) * .75) - ((temdfp[target]) / 2));
		if(damage < 0)
		{
			damage = 0;
		}
		tehp[target] = tehp[target] - damage;
		mp[sequence[i]] = mp[sequence[i]] - 3;
		cout << charname[sequence[i]] << " casts Ice I. " << tename[target] << " is damaged for " << damage << " HP. \n";
		if((tehp[target]) < 0)
		{
			edeath();
		}	
	}
	//ATPUP I
	else if((spellnum == 7) && ((mp[sequence[i]]) >= 3))
	{
		atpplus[target] = 10;
		atpduration[target] = 2;
		mp[sequence[i]] = mp[sequence[i]] - 3;
		cout << charname[sequence[i]] << " casts ATPUP I. " << charname[target] << "'s attack increases. \n";
	}
	//Black Hole I
	else if((spellnum == 8) && ((mp[sequence[i]]) >= 10))
	{
		tehp[target] = (tehp[target] * .5);
		mp[sequence[i]] = mp[sequence[i]] - 10;
		cout << charname[sequence[i]] << " casts Black Hole I. " << tename[target] << "'s life is drained. \n";
		if(tehp[target] == 0)
		{
			tehp[target] = 1;
		}
	}

	//Level II Spells
	//Heal II
	else if((spellnum == 9) && ((mp[sequence[i]]) >= 6))
	{
		if(hp[target] != 0)
		{
			damage = (((ucmatp[sequence[i]]) + (uematp[sequence[i]])) * 1.25);
			hp[target] = hp[target] + damage;
			mp[sequence[i]] = mp[sequence[i]] - 6;
			if((hp[target]) > (uchpmax[target]))
			{
				hp[target] = uchpmax[target];
			}
			cout << charname[sequence[i]] << " casts Heal II. " << charname[target] << " is healed for " << damage << " HP. \n";
		}
		else
		{
			cout << charname[target] << " is dead! \n";
			turn = 0;
		}
	}
	//Light II
	else if((spellnum == 10) && ((mp[sequence[i]]) >= 8))
	{
		damage = ((((ucmatp[sequence[i]]) + (uematp[sequence[i]])) * 1.25) - ((temdfp[target]) / 2));
		if(damage < 0)
		{
			damage = 0;
		}
		tehp[target] = tehp[target] - damage;
		mp[sequence[i]] = mp[sequence[i]] - 8;
		cout << charname[sequence[i]] << " casts Light II. " << tename[target] << " is damaged for " << damage << " HP. \n";
		if((tehp[target]) < 0)
		{
			edeath();
		}
	}
	//DFPUP II
	else if((spellnum == 11) && ((mp[sequence[i]]) >= 6))
	{
		dfpplus[target] = 20;
		dfpduration[target] = 3;
		mp[sequence[i]] = mp[sequence[i]] - 6;
		cout << charname[sequence[i]] << " casts DFPUP II. " << charname[target] << "'s defense increases. \n";	
	}
	//Resurrect II
	else if((spellnum == 12) && ((mp[sequence[i]]) >= 30))
	{
		if(hp[target] == 0)
		{
			hp[target] = (uchpmax[target] * .5);
			mp[sequence[i]] = mp[sequence[i]] - 30;
			cremain = cremain + 1;
			cout << charname[sequence[i]] << " casts Resurrect II. " << charname[target] << " is revived. \n";
		}
		else
		{
			cout << charname[target] << " is not dead! \n";
			turn = 0;
		}
	}
	//Fire II
	else if((spellnum == 13) && ((mp[sequence[i]]) >= 5))
	{
		damage = ((((ucmatp[sequence[i]]) + (uematp[sequence[i]])) * 1) - ((temdfp[target]) / 2));
		if(damage < 0)
		{
			damage = 0;
		}
		tehp[target] = tehp[target] - damage;
		mp[sequence[i]] = mp[sequence[i]] - 5;
		cout << charname[sequence[i]] << " casts Fire II. " << tename[target] << " is damaged for " << damage << " HP. \n";
		if((tehp[target]) < 0)
		{
			edeath();
		}	
	}
	//Ice II
	else if((spellnum == 14) && ((mp[sequence[i]]) >= 6))
	{
		damage = ((((ucmatp[sequence[i]]) + (uematp[sequence[i]])) * 1.25) - ((temdfp[target]) / 2));
		if(damage < 0)
		{
			damage = 0;
		}
		tehp[target] = tehp[target] - damage;
		mp[sequence[i]] = mp[sequence[i]] - 6;
		cout << charname[sequence[i]] << " casts Ice II. " << tename[target] << " is damaged for " << damage << " HP. \n";
		if((tehp[target]) < 0)
		{
			edeath();
		}
	}
	//ATPUP II
	else if((spellnum == 15) && ((mp[sequence[i]]) >= 6))
	{
		atpplus[target] = 20;
		atpduration[target] = 3;
		mp[sequence[i]] = mp[sequence[i]] - 6;
		cout << charname[sequence[i]] << " casts ATPUP II. " << charname[target] << "'s attack increases. \n";
	}
	//Black Hole II
	else if((spellnum == 16) && ((mp[sequence[i]]) >= 15))
	{
		tehp[target] = (tehp[target] * .25);
		mp[sequence[i]] = mp[sequence[i]] - 15;
		cout << charname[sequence[i]] << " casts Black Hole II. " << tename[target] << "'s life is drained. \n";
		if(tehp[target] == 0)
		{
			tehp[target] = 1;
		}
	}

	//Level III Spells
	//Heal III
	else if((spellnum == 17) && ((mp[sequence[i]]) >= 12))
	{
		if(hp[target] != 0)
		{
			hp[target] = uchpmax[target];
			mp[sequence[i]] = mp[sequence[i]] - 12;
			cout << charname[sequence[i]] << " casts Heal III. " << charname[target] << " is fully healed. \n";	
		}
		else
		{
			cout << charname[target] << " is dead! \n";
			turn = 0;
		}
	}
	//Light III
	else if((spellnum == 18) && ((mp[sequence[i]]) >= 16))
	{
		damage = ((((ucmatp[sequence[i]]) + (uematp[sequence[i]])) * 1.75) - ((temdfp[target]) / 2));
		if(damage < 0)
		{
			damage = 0;
		}
		tehp[target] = tehp[target] - damage;
		mp[sequence[i]] = mp[sequence[i]] - 16;
		cout << charname[sequence[i]] << " casts Light III. " << tename[target] << " is damaged for " << damage << " HP. \n";
		if((tehp[target]) < 0)
		{
			edeath();
		}
	}
	//DFPUP III
	else if((spellnum == 19) && ((mp[sequence[i]]) >= 10))
	{
		dfpplus[target] = 30;
		dfpduration[target] = 4;
		cout << charname[sequence[i]] << " casts DFPUP III. " << charname[target] << "'s defense increases. \n";
		mp[sequence[i]] = mp[sequence[i]] - 10;
	}
	//Resurrect III
	else if((spellnum == 20) && ((mp[sequence[i]]) >= 40))
	{
		if(hp[target] == 0)
		{
			hp[target] = uchpmax[target];
			mp[sequence[i]] = mp[sequence[i]] - 40;
			cremain = cremain + 1;
			cout << charname[sequence[i]] << " casts Resurrect III. " << charname[target] << " is revived. \n";
		}
		else
		{
			cout << charname[target] << " is not dead! \n";
			turn = 0;
		}
	}
	//Fire III
	else if((spellnum == 21) && ((mp[sequence[i]]) >= 10))
	{
		damage = ((((ucmatp[sequence[i]]) + (uematp[sequence[i]])) * 1.5) - ((temdfp[target]) / 2));
		if(damage < 0)
		{
			damage = 0;
		}
		tehp[target] = tehp[target] - damage;
		mp[sequence[i]] = mp[sequence[i]] - 10;
		cout << charname[sequence[i]] << " casts Fire III. " << tename[target] << " is damaged for " << damage << " HP. \n";
		if((tehp[target]) < 0)
		{
			edeath();
		}	
	}
	//Ice III
	else if((spellnum == 22) && ((mp[sequence[i]]) >= 12))
	{
		damage = ((((ucmatp[sequence[i]]) + (uematp[sequence[i]])) * 1.75) - ((temdfp[target]) / 2));
		if(damage < 0)
		{
			damage = 0;
		}
		tehp[target] = tehp[target] - damage;
		mp[sequence[i]] = mp[sequence[i]] - 12;
		cout << charname[sequence[i]] << " casts Ice III. " << tename[target] << " is damaged for " << damage << " HP. \n";
		if((tehp[target]) < 0)
		{
			edeath();
		}
	}
	//ATPUP III
	else if((spellnum == 23) && ((mp[sequence[i]]) >= 10))
	{
		atpplus[target] = 30;
		atpduration[target] = 4;
		mp[sequence[i]] = mp[sequence[i]] - 10;
		cout << charname[sequence[i]] << " casts ATPUP III. " << charname[target] << "'s attack increases. \n";
	}
	//Black Hole III
	else if((spellnum == 24) && ((mp[sequence[i]]) >= 25))
	{
		tehp[target] = 1;
		mp[sequence[i]] = mp[sequence[i]] - 25;
		cout << charname[sequence[i]] << " casts Black Hole III. " << tename[target] << "'s life is drained. \n";
	}

	//Insufficient MP
	else
	{
		cout << charname[sequence[i]] << " does not have enough MP to cast this spell. \n";
		turn = 0;
	}
}

void itemuse()
{
	//failsafe loop check
	itemnum[0] = 1;
	cout << "Select the item you wish to use: \n"
		 << " 0) Cancel \n"
		 << " 1) Healing Potion         x " << itemnum[1] << '\n'
		 << " 2) Extra Healing Potion   x " << itemnum[2] << '\n'
		 << " 3) Elixir of Healing      x " << itemnum[3] << '\n'
		 << " 4) Ether Potion           x " << itemnum[4] << '\n'
		 << " 5) Extra Ether Potion     x " << itemnum[5] << '\n'
		 << " 6) Resurrection Vial      x " << itemnum[6] << '\n';
	do
	{
		cin >> itemchoice;
		if((itemnum[itemchoice] <= 0) && (itemchoice != 0))
		{
			cout << "You do not have any of that item. \n";
		}
	}
	while((itemchoice < 0) || (itemchoice > 7) || (itemnum[itemchoice] <= 0));
	if(itemchoice != 0)
	{
		system("CLS");
		battlescreen();
		turn = 1;
		cout << "Select a Target: \n";
		cout << "1) " << charname[1] << '\n'
			 << "2) " << charname[2] << '\n'
			 << "3) " << charname[3] << '\n';
		do
		{
			cin >> target;
		}
		while(((target < 1) || (target > 3)));
		system("CLS");
		battlescreen();
		switch(itemchoice)
		{
		case 1:
			if(hp[target] != 0)
			{
				hp[target] = hp[target] + 30;
				if((hp[target]) > (uchpmax[target]))
				{
					hp[target] = uchpmax[target];
				}
				itemnum[itemchoice] = itemnum[itemchoice] - 1;
				cout << charname[sequence[i]] << " used a Healing Potion. " << charname[target] << " is healed for 30 HP. \n";
			}
			else
			{
				cout << charname[target] << " is dead! \n";
			}
			break;
		case 2:
			if(hp[target] != 0)
			{
				hp[target] = hp[target] + 60;
				if((hp[target]) > (uchpmax[target]))
				{
					hp[target] = uchpmax[target];
				}
				itemnum[itemchoice] = itemnum[itemchoice] - 1;
				cout << charname[sequence[i]] << " used an Extra Healing Potion. " << charname[target] << " is healed for 60 HP. \n";
			}
			else
			{
				cout << charname[target] << " is dead! \n";
			}
			break;
		case 3:
			if(hp[target] != 0)
			{
				hp[target] = uchpmax[target];
				itemnum[itemchoice] = itemnum[itemchoice] - 1;
				cout << charname[sequence[i]] << " used an Elixir of Healing. " << charname[target] << " is fully healed. \n";
			}
			else
			{
				cout << charname[target] << " is dead! \n";
			}
			break;
		case 4:
			if(hp[target] != 0)
			{	
				mp[target] = mp[target] + 30;
				if((mp[target]) > (ucmpmax[target]))
				{
					mp[target] = ucmpmax[target];
				}
				itemnum[itemchoice] = itemnum[itemchoice] - 1;
				cout << charname[sequence[i]] << " used an Ether Potion. " << charname[target] << " is healed for 30 MP. \n";
			}
			else
			{
				cout << charname[target] << " is dead! \n";
			}
			break;
		case 5:
			if(hp[target] != 0)
			{
				mp[target] = mp[target] + 60;
				if((mp[target]) > (ucmpmax[target]))
				{
					mp[target] = ucmpmax[target];
				}
				itemnum[itemchoice] = itemnum[itemchoice] - 1;
				cout << charname[sequence[i]] << " used an Extra Ether Potion. " << charname[target] << " is healed for 60 MP. \n";
			}
			else
			{
				cout << charname[target] << " is dead! \n";
			}
			break;
		case 6:
			if((hp[target]) == 0)
			{
				hp[target] = (uchpmax[target] * .1);
				itemnum[itemchoice] = itemnum[itemchoice] - 1;
				cout << charname[sequence[i]] << " used a Resurrection Vial. " << charname[target] << " is revived. \n";
				cremain = cremain + 1;
			}
			else
			{
				cout << charname[target] << " is not dead! \n";
				turn = 0;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		turn = 0;
	}
}

void edeath()
{
	tehp[target] = 0;
	eremain = eremain - 1;
	cout << tename[target] << " is slain. \n";
	//Exp and Gold Gain
	gainedxp = gainedxp + ((teatp[target]) + (tedfp[target]) + (tematp[target]) + (temdfp[target])) * 2;
	gainedgold = gainedgold + (((teatp[target]) + (tedfp[target]) + (tematp[target]) + (temdfp[target])) * 2);
	if(eremain == 0)
	{
		//for-loop forced end
		i = enemycount + 2;
	}
	//Temp Enemy stats set to 0
	strcpy_s(tename[target], "");
	televel[target] = 0;
	tehpmax[target] = 0;
	teatp[target] = 0;
	tedfp[target] = 0;
	tempmax[target] = 0;
	tematp[target] = 0;
	temdfp[target] = 0;
	tespd[target] = 0;
	tehp[target] = tehpmax[target];
	temp[target] = tempmax[target];
}


void shop()
{
	do
	{
	 system("CLS");
	 if(towncheck==1)
	 {
		 cout<<"  ------------------------      -------------\n";
		 cout<<" *   Chad the Alchemist   *     Gold: "<<gold<<"\n";
		 cout<<"  ------------------------      -------------\n";
		 cout<<"   Item            Price\n";
		 cout<<"------------------------------\n";
		 
	 }
	 else if(towncheck==2)
	 {
		 cout<<"  -----------------------      -------------\n";
		 cout<<" *   Jon the Alchemist   *     Gold: "<<gold<<"\n";
		 cout<<"  -----------------------      -------------\n";
		 cout<<"   Item            Price\n";
		 cout<<"------------------------------\n";
		 
	 }
	 else if(towncheck==3)
	 {
		 cout<<"  -----------------------------      -------------\n";
		 cout<<" *   Cassandra the Alchemist   *     Gold: "<<gold<<"\n";
		 cout<<"  -----------------------------      -------------\n";
		 cout<<"   Item            Price\n";
		 cout<<"------------------------------\n";
		
	 }
	 else if(towncheck==4)
	 {
		 cout<<"  ----------------------------      -------------\n";
		 cout<<" *   Mlle Iva the Alchemist   *     Gold: "<<gold<<"\n";
		 cout<<"  ----------------------------      -------------\n";
		 cout<<"   Item            Price\n";
		 cout<<"------------------------------\n";
		 
	 }
	 else if(towncheck==5)
	 {
		 cout<<"  ---------------------------      -------------\n";
		 cout<<" *   Katrina the Alchemist   *     Gold: "<<gold<<"\n";
		 cout<<"  ---------------------------      -------------\n";
		 cout<<"   Item            Price\n";
		 cout<<"------------------------------\n";
		 
	 }
	 else if(towncheck==6)
	 {
		 cout<<"  -------------------------      ------------\n";
		 cout<<" *   Pyrus the Alchemist   *     Gold: "<<gold<<"\n";
		 cout<<"  -------------------------      -------------\n";
		 cout<<"   Item                  Price\n";
		 cout<<"------------------------------\n";
		 
	 }
	     cout<<"1.)Healing Potion   	 350 G\n";
		 cout<<"2.)Extra Healing Potion  600 G\n";
		 cout<<"3.)Elixir of Healing    1000 G\n";
		 cout<<"4.)Ether Potion          320 G\n";
		 cout<<"5.)Extra Ether Potion    550 G\n";
		 cout<<"6.)Resurrection Vial     875 G\n";
		 cout<<"-------------------------------------\n";
		 cout<<"Make your choice (Press 0 to exit): ";
		 cin>>shoppick;
		 if(shoppick==1)
		 {
			 cout<<"\n";
			 cout<<"How many would you like to purchase?: ";
			 cin>>numpur;
			 if(numpur<=0)
			 {
				 cout<<"Alchemist: That quantity is too low.\n";
				 cout<<"\n";
				 cout<<"Press 1 to continue: ";
				 cin>>one;
			 }
			 else if(numpur>0)
			 {
				 totalam=350*numpur;
				 cout<<"\n";
				 cout<<"Item: Healing Potion   Quantity: "<<numpur<<"   Total Price: "<<totalam<<" G\n";
				 cout<<"\n";
				 if (gold<totalam)
				 {
					 
					 cout<<"Alchemist: Sorry you do not have enough gold for that quantity.\n";
					 cout<<"\n";
					 cout<<"Press 1 to continue: ";
					 cin>>one;
				 }
				 else if(gold>=totalam)
				 {
					 itemnum[shoppick]=itemnum[shoppick]+numpur;
					 gold=gold-totalam;
					 
					 cout<<"Alchemist: Thank you for your purchase. You have added "<<numpur<<"\n";
					 cout<<"Alchemist: Healing Potion(s) to your inventory.\n";
					 cout<<"\n";
					 cout<<"Press 1 to continue: ";
					 cin>>one;
				 }
			 }

		 }
		 else if(shoppick==2)
		 {
			 cout<<"\n";
			 cout<<"How many would you like to purchase?: ";
			 cin>>numpur;
			 if(numpur<=0)
			 {
				 cout<<"Alchemist: That quantity is too low.\n";
				 cout<<"\n";
				 cout<<"Press 1 to continue: ";
				 cin>>one;
			 }
			 else if(numpur>0)
			 {
				 totalam=600*numpur;
				 cout<<"\n";
				 cout<<"Item: Extra Healing Potion   Quantity: "<<numpur<<"   Total Price: "<<totalam<<" G\n";
				 cout<<"\n";
				 if (gold<totalam)
				 {
					 
					 cout<<"Alchemist: Sorry you do not have enough gold for that quantity.\n";
					 cout<<"\n";
					 cout<<"Press 1 to continue: ";
					 cin>>one;
				 }
				 else if(gold>=totalam)
				 {
					 itemnum[shoppick]=itemnum[shoppick]+numpur;
					 gold=gold-totalam;
					 
					 cout<<"Alchemist: Thank you for your purchase. You have added "<<numpur<<"\n";
					 cout<<"Alchemist: Extra Healing Potion(s) to your inventory.\n";
					 cout<<"\n";
					 cout<<"Press 1 to continue: ";
					 cin>>one;
				 }
			 }

		 }
		 else if(shoppick==3)
		 {
			 cout<<"\n";
			 cout<<"How many would you like to purchase?: ";
			 cin>>numpur;
			 if(numpur<=0)
			 {
				 cout<<"Alchemist: That quantity is too low.\n";
				 cout<<"\n";
				 cout<<"Press 1 to continue: ";
				 cin>>one;
			 }
			 else if(numpur>0)
			 {
				 totalam=1000*numpur;
				 cout<<"\n";
				 cout<<"Item: Elixir of Healing   Quantity: "<<numpur<<"   Total Price: "<<totalam<<" G\n";
				 cout<<"\n";
				 if (gold<totalam)
				 {
					 
					 cout<<"Alchemist: Sorry you do not have enough gold for that quantity.\n";
					 cout<<"\n";
					 cout<<"Press 1 to continue: ";
					 cin>>one;
				 }
				 else if(gold>=totalam)
				 {
					 itemnum[shoppick]=itemnum[shoppick]+numpur;
					 gold=gold-totalam;
					 
					 cout<<"Alchemist: Thank you for your purchase. You have added "<<numpur<<"\n";
					 cout<<"Alchemist: Elixir(s) of Healing to your inventory.\n";
					 cout<<"\n";
					 cout<<"Press 1 to continue: ";
					 cin>>one;
				 }
			 }

		 }
		 else if(shoppick==4)
		 {
			 cout<<"\n";
			 cout<<"How many would you like to purchase?: ";
			 cin>>numpur;
			 if(numpur<=0)
			 {
				 cout<<"Alchemist: That quantity is too low.\n";
				 cout<<"\n";
				 cout<<"Press 1 to continue: ";
				 cin>>one;
			 }
			 else if(numpur>0)
			 {
				 totalam=320*numpur;
				 cout<<"\n";
				 cout<<"Item: Ether Potion   Quantity: "<<numpur<<"   Total Price: "<<totalam<<" G\n";
				 cout<<"\n";
				 if (gold<totalam)
				 {
					 
					 cout<<"Alchemist: Sorry you do not have enough gold for that quantity.\n";
					 cout<<"\n";
					 cout<<"Press 1 to continue: ";
					 cin>>one;
				 }
				 else if(gold>=totalam)
				 {
					 itemnum[shoppick]=itemnum[shoppick]+numpur;
					 gold=gold-totalam;
					 
					 cout<<"Alchemist: Thank you for your purchase. You have added "<<numpur<<"\n";
					 cout<<"Alchemist: Ether Potion(s) to your inventory.\n";
					 cout<<"\n";
					 cout<<"Press 1 to continue: ";
					 cin>>one;
				 }
			 }

		 }
		 else if(shoppick==5)
		 {
			 cout<<"\n";
			 cout<<"How many would you like to purchase?: ";
			 cin>>numpur;
			 if(numpur<=0)
			 {
				 cout<<"Alchemist: That quantity is too low.\n";
				 cout<<"\n";
				 cout<<"Press 1 to continue: ";
				 cin>>one;
			 }
			 else if(numpur>0)
			 {
				 totalam=550*numpur;
				 cout<<"\n";
				 cout<<"Item: Extra Ether Potion  Quantity: "<<numpur<<"   Total Price: "<<totalam<<" G\n";
				 cout<<"\n";
				 if (gold<totalam)
				 {
					 
					 cout<<"Alchemist: Sorry you do not have enough gold for that quantity.\n";
					 cout<<"\n";
					 cout<<"Press 1 to continue: ";
					 cin>>one;
				 }
				 else if(gold>=totalam)
				 {
					 itemnum[shoppick]=itemnum[shoppick]+numpur;
					 gold=gold-totalam;
					 
					 cout<<"Alchemist: Thank you for your purchase. You have added "<<numpur<<"\n";
					 cout<<"Alchemist: Extra Ether Potion(s) to your inventory.\n";
					 cout<<"\n";
					 cout<<"Press 1 to continue: ";
					 cin>>one;
				 }
			 }

		 }
		 else if(shoppick==6)
		 {
			 cout<<"\n";
			 cout<<"How many would you like to purchase?: ";
			 cin>>numpur;
			 if(numpur<=0)
			 {
				 cout<<"Alchemist: That quantity is too low.\n";
				 cout<<"\n";
				 cout<<"Press 1 to continue: ";
				 cin>>one;
			 }
			 else if(numpur>0)
			 {
				 totalam=875*numpur;
				 cout<<"\n";
				 cout<<"Item: Resurrection Vial   Quantity: "<<numpur<<"   Total Price: "<<totalam<<" G\n";
				 cout<<"\n";
				 if (gold<totalam)
				 {
					 
					 cout<<"Alchemist: Sorry you do not have enough gold for that quantity.\n";
					 cout<<"\n";
					 cout<<"Press 1 to continue: ";
					 cin>>one;
				 }
				 else if(gold>=totalam)
				 {
					 itemnum[shoppick]=itemnum[shoppick]+numpur;
					 gold=gold-totalam;
					 
					 cout<<"Alchemist: Thank you for your purchase. You have added "<<numpur<<"\n";
					 cout<<"Alchemist: Resurrection Vial(s) to your inventory.\n";
					 cout<<"\n";
					 cout<<"Press 1 to continue: ";
					 cin>>one;
				 }
			 }

		 }
		 
		 

	}
	while (shoppick!=0);

}

//DOJO

void dojo()
{	
	
		if (towncheck==1)
		{
			dojoclass=6;
			dojoclass2=12;
			dojoclass3=18;
		}
		else if(towncheck==2)
		{
			dojoclass=5;
			dojoclass2=11;
			dojoclass3=17;
		}
		else if(towncheck==3)
		{
			dojoclass=3;
			dojoclass2=9;
			dojoclass3=15;
		}
		else if(towncheck==4)
		{
			dojoclass=4;
			dojoclass2=10;
			dojoclass3=16;
		}
		else if(towncheck==5)
		{
			dojoclass=2;
			dojoclass2=8;
			dojoclass3=14;
		}
		else if(towncheck==6)
		{
			dojoclass=1;
			dojoclass=7;
			dojoclass=13;
		}
	do
	{
		system("CLS");
		dojoname();
		cout<<"Master: I will train you to be faster, stronger, better.\n";
		cout<<"\n";
		dojocharselect();
		cout<<"4.)Leave\n";
		cout<<"Choose a character: ";
		cin>>dojochar;
		if((dojochar>=1) && (dojochar<=3))
		{
			if(dojoclass3==charclass[dojochar])
			{
				system("CLS");
				dojoname();
				cout<<"Master: You have reached your highest rank.\n";
				cout<<"Master: Now get out of here, and good luck you your journey.\n";
				cout<<"\n";
				cout<<"Press 1 to continue: ";
				cin>>one;
			}

			
			else if(dojoclass2==charclass[dojochar])
			{	
				system("CLS");
				dojoname();
				cout<<"Master: You are weak. You must learn the ways of the "<<classname[dojoclass3]<<".\n";
				cout<<"Master: I will train you, however it will cost you a fee.\n";
				cout<<"Master: You are nothing, but you can be something.\n";
				cout<<"Master: The fee is 700G.\n";
				cout<<"\n";
				cout<<"Train?\n";
				cout<<"1.)Yes\n";
				cout<<"2.)No\n";
				cout<<"Make your choice: ";
				cin>>train;	
				
				if(train==1)
				{
					if(level[dojochar]<30)
					{
						system("CLS");
						dojoname();
						cout<<"Master: You are not experienced enough for my training.\n";
						cout<<"Master: Come back when you have fought hard and leveled up.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
					else if(level[dojochar]>=30)
					{
						
						if (gold<700)
						{
							cout<<"Master: You are wasting my time, you do not have the funds for training\n";
							cout<<"Master: Leave my dojo now, and return with more gold.\n";
							cout<<"\n";
							cout<<"Press 1 to continue\n";
							cin>>one;
						}
						else if(gold>=700)
						{
							system("CLS");
							dojoname();
							cout<<"*After days of long training the time has come.\n";
							cout<<"\n";
							cout<<"Master: Congratulations young one, you have passed my training.\n";
							cout<<"Master: Come and see me again soon.\n";
							cout<<"\n";
							cout<<"*Have completed training you have upraded your class\n";
							charclass[dojochar]=charclass[dojochar]+6;
							cout<<"Old Class: "<<classname[dojoclass]<<"    Current Class: "<<classname[charclass[dojochar]]<<'\n';
							cout<<"\n";
							gold=gold-700;
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
					}
				}
			}

			else if(dojoclass==charclass[dojochar])
			{	
				system("CLS");
				dojoname();
				cout<<"Master: You are weak. You must learn the ways of the "<<classname[dojoclass2]<<".\n";
				cout<<"Master: I will train you, however it will cost you a fee.\n";
				cout<<"Master: You are nothing, but you can be something.\n";
				cout<<"Master: The fee is 700G.\n";
				cout<<"\n";
				cout<<"Train?\n";
				cout<<"1.)Yes\n";
				cout<<"2.)No\n";
				cout<<"Make your choice: ";
				cin>>train;	
				
				if(train==1)
				{
					if(level[dojochar]<15)
					{
						system("CLS");
						dojoname();
						cout<<"Master: You are not experienced enough for my training.\n";
						cout<<"Master: Come back when you have fought hard and leveled up.\n";
						cout<<"\n";
						cout<<"Press 1 to continue: ";
						cin>>one;
					}
					else if(level[dojochar]>=15)
					{
						
						if (gold<700)
						{
							cout<<"Master: You are wasting my time, you do not have the funds for training\n";
							cout<<"Master: Leave my dojo now, and return with more gold.\n";
							cout<<"\n";
							cout<<"Press 1 to continue\n";
							cin>>one;
						}
						else if(gold>=700)
						{
							system("CLS");
							dojoname();
							cout<<"*After days of long training the time has come.\n";
							cout<<"\n";
							cout<<"Master: Congratulations young one, you have passed my training.\n";
							cout<<"Master: Come and see me again soon.\n";
							cout<<"\n";
							cout<<"*Have completed training you have upraded your class\n";
							charclass[dojochar]=charclass[dojochar]+6;
							cout<<"Old Class: "<<classname[dojoclass]<<"    Current Class: "<<classname[charclass[dojochar]]<<'\n';
							cout<<"\n";
							gold=gold-700;
							cout<<"Press 1 to continue: ";
							cin>>one;
						}
					}
				}
				
			}
			else if((dojoclass!=charclass[dojochar]) || (dojoclass2!=charclass[dojochar]) || (dojoclass3!=charclass[dojochar]))
			{
				cout<<"\n";
				cout<<"Master: I am unable to train your class at this dojo.\n";
				cout<<"\n";
				cout<<"Press 1 to continue: \n";
				cin>>one;
			}
		}

	}
	while(dojochar!=4);
		
	
}

void dojoname()
{
	if(towncheck==1)
	{
		cout<<"  ---------------\n";
		cout<<" * Wizard's Keep *\n";
		cout<<"  ---------------\n";
	}
	else if(towncheck==2)
	{
		cout<<"  ------------\n";
		cout<<" * Guild Hall *\n";
		cout<<"  ------------\n";
	}
	else if(towncheck==3)
	{
		cout<<"  ---------------\n";
		cout<<" * The Holy Arch *\n";
		cout<<"  ---------------\n";
	}
	else if(towncheck==4)
	{
		cout<<"  ---------\n";
		cout<<" * Ys Dojo *\n";
		cout<<"  ---------\n";
	}
	else if(towncheck==5)
	{
		cout<<"  ---------------\n";
		cout<<" * Hidden Grotto *\n";
		cout<<"  ---------------\n";
	}
	else if(towncheck==6)
	{
		cout<<"  --------------\n";
		cout<<" * Kyme's Place *\n";
		cout<<"  --------------\n";
	}
}

//Church
void church()
{
	do
	{
	 system("CLS");
	 if(towncheck==1)
	 {
		 cout<<"  ----------------------------      -------------\n";
		 cout<<" *   Lille House of Worship   *     Gold: "<<gold<<"\n";
		 cout<<"  ----------------------------      -------------\n"; 
	 }
	 else if(towncheck==2)
	 {
		 cout<<"  ----------------------      -------------\n";
		 cout<<" *   Karas Cathedral   *     Gold: "<<gold<<"\n";
		 cout<<"  ----------------------      -------------\n";	 
	 }
	 else if(towncheck==3)
	 {
		 cout<<"  ------------------      -------------\n";
		 cout<<" *   Cross of God   *     Gold: "<<gold<<"\n";
		 cout<<"  ------------------      -------------\n";	
	 }
	 else if(towncheck==4)
	 {
		 cout<<"  ----------------------      -------------\n";
		 cout<<" *   First Ulm Church   *     Gold: "<<gold<<"\n";
		 cout<<"  ----------------------      -------------\n";
		 
	 }
	 else if(towncheck==5)
	 {
		 cout<<"  ----------------------      -------------\n";
		 cout<<" *   Church of Trevia   *     Gold: "<<gold<<"\n";
		 cout<<"  ----------------------      -------------\n";
	 }
	 else if(towncheck==6)
	 {
		 cout<<"  ---------------      ------------\n";
		 cout<<" *   Holy Rien   *     Gold: "<<gold<<"\n";
		 cout<<"  ---------------      -------------\n";	 
	 }
	 cout<<"Priest: The cost to revive a character is 500G.\n";
	 cout<<"\n";
	 cout<<"1.)"<<charname[1]<<" HP: "<<hp[1]<<"/"<<uchpmax[1]<<'\n';
	 cout<<"2.)"<<charname[2]<<" HP: "<<hp[2]<<"/"<<uchpmax[2]<<'\n';
	 cout<<"3.)"<<charname[3]<<" HP: "<<hp[3]<<"/"<<uchpmax[3]<<'\n';
	 cout<<"4.)Leave Church\n";
	 cout<<"Select a character that needs to be revived: ";
	 cin>>churchpick;
	 if( (churchpick>=1) && (churchpick<=3))
	 {
		 cout<<"--------------------------\n";

		 if(hp[churchpick]!=0)
		 {
			 cout<<"Priest: "<<charname[churchpick]<<" does not need to be revived.\n";
			 cout<<"\n";
			 cout<<"Press 1 to continue: ";
			 cin>>one;
		 }
		 else if(hp[churchpick]==0)
		 {
			 if(gold<500)
			 {
				 cout<<"Priest: I am sorry you do not have enough gold.\n";
				 cout<<"Priest: My services are costly, come back again.\n";
				 cout<<"\n";
				 cout<<"Press 1 to continue: ";
				 cin>>one;
			 }
			 else if(gold>=500)
			 {
				cout<<"Priest: I shall revive "<<charname[churchpick]<<".\n";
				cout<<"Priest: Thank you for your time, and good luck on your journey.\n";
				gold=gold-500;
				cremain=cremain+1;
				hp[churchpick]=(uchpmax[churchpick]/2);
				cout<<"\n";
				cout<<"Press 1 to continue: ";
				cin>>one;
			 }
		 }
	 }




	}
	while (churchpick!=4);
}



void dungeonmain()
{
	do
	{
		system("CLS");
		//Main Dungeon Screen
		system("CLS");
		cout << dungeonname[dungeonnum] << '\n'
			 << "---------------\n"
		     << "X Position: " << dungeonx << '\n'
		     << "Y Position: " << dungeony << '\n'
		     << "---------------\n"
			 << "\n"
			 << "1.)Travel North         2.)Travel East \n"
		     << "3.)Travel South         4.)Travel West \n"
		     << "5.)Use Healing Magic    6.)Use Items \n"
		     << "7.)View Statistics      8.)Search the Area\n"
		     << "------------------------------------------------\n"
			 << "Select an option: ";
		do
		{
			cin >> dungeonchoice;
		}
		while((dungeonchoice < 1) || (dungeonchoice > 8));
		switch(dungeonchoice)
		{
		case 1:
			//North
			if(dungeony == dnorthlimit[dungeonnum])
			{
				cout << "You are unable to move in that direction. \n";
				cout << "Press 1 to continue ";
				cin >> one;
			}
			else
			{
				dungeony = dungeony + 1;
				step = step + 1;
				//Battle Check
				x = rand() % 10;
				if(step > x)
				{
					cout << "Enemies approach... \n";
					cout << "Press 1 to continue \n";
					cin >> one;
					battle();
					step = 0;
				}
			}
			break;
		case 2:
			//East
			if(dungeonx == deastlimit[dungeonnum])
			{
				cout << "You are unable to move in that direction. \n";
				cout << "Press 1 to continue ";
				cin >> one;
			}
			else
			{
				dungeonx = dungeonx + 1;
				step = step + 1;
				//Battle Check
				x = rand() % 10;
				if(step > x)
				{
					cout << "Enemies approach... \n";
					cout << "Press 1 to continue \n";
					cin >> one;
					battle();
					step = 0;
				}
			}
			break;
		case 3:
			//South
			if(dungeony == dsouthlimit[dungeonnum])
			{
				cout << "You are unable to move in that direction. \n";
				cout << "Press 1 to continue ";
				cin >> one;
			}
			else
			{
				dungeony = dungeony - 1;
				step = step + 1;
				//Battle Check
				x = rand() % 10;
				if(step > x)
				{
					cout << "Enemies approach... \n";
					cout << "Press 1 to continue \n";
					cin >> one;
					battle();
					step = 0;
				}
			}
			break;
		case 4:
			//West
			if(dungeonx == dwestlimit[dungeonnum])
			{
				cout << "You are unable to move in that direction. \n";
				cout << "Press 1 to continue ";
				cin >> one;
			}
			else
			{
				dungeonx = dungeonx - 1;
				step = step + 1;
				//Battle Check
				x = rand() % 10;
				if(step > x)
				{
					cout << "Enemies approach... \n";
					cout << "Press 1 to continue \n";
					cin >> one;
					battle();
					step = 0;
				}
			}
			break;
		case 5:
			//Use Healing Magic
			healmagicuse();
			break;
		case 6:
			//Use Items
			itemuse();
			break;
		case 7:
			//View Statistics
			cout << "Press 1 to continue: ";
			cin >> one;
			status();
			break;
		case 8:
			//Search
			search();
			break;
		default:
			break;
		}
	}
	while(dexitcheck != 1);	
}

void search()
{
	system("CLS");
	cout << "You carefully search the area... \n";
	//Entrance Location
	if((dungeonx == dexitx[dungeonnum]) && (dungeony == dexity[dungeonnum]))
	{
		cout << "and you find the exit. \n";
		cout << "Would you like to exit the dungeon? \n";
		cout << "1.) Yes       2.) No \n";
		cin >> dexitcheck;
	}
	//Item Location
	else if((dungeonx == ditemx[dungeonnum]) && (dungeony == ditemy[dungeonnum]))
	{
		//Item Check
		if(ditemcheck[dungeonnum] == 1)
		{
			//3 = Adamantium Armor	(Rien, Mallow Marsh, Fighter)
			if(dungeonnum == 1)
			{
				cout << "and find the fabled Adamantium Armor, \n"
					 << "which only a Holy Warrior can equip. \n"
					 << "Who among your party will attempt to wear the armor? \n"
					 << "1.) " << charname[1] << " the " << classname[charclass[1]] << '\n'
					 << "2.) " << charname[2] << " the " << classname[charclass[2]] << '\n'
					 << "3.) " << charname[3] << " the " << classname[charclass[3]] << '\n';
				do
				{
					cin >> searchchoice;
				}
				while((searchchoice < 1) || (searchchoice > 3));
				if(hp[searchchoice] == 0)
				{
					cout << charname[searchchoice] << " is dead! \n";
				}
				else if(charclass[searchchoice] != 13)
				{
					cout << charname[searchchoice] << " is not able to wear this armor! \n";
				}
				else
				{
					cout << charname[searchchoice] << " equips the fabled Adamantium Armor! \n";
					ditemcheck[dungeonnum] = 0;
					armor[searchchoice] = 3;
					i = searchchoice;
					statcalc();
				}
			}
			//3 = Excalibur			(Rien, Hidden Everglades, Fighter)
			else if(dungeonnum == 2)
			{
				cout << "and find the legendary Excalibur, \n"
					 << "which only a Holy Warrior can equip. \n"
					 << "Who among your party will attempt to wield this weapon? \n"
					 << "1.) " << charname[1] << " the " << classname[charclass[1]] << '\n'
					 << "2.) " << charname[2] << " the " << classname[charclass[2]] << '\n'
					 << "3.) " << charname[3] << " the " << classname[charclass[3]] << '\n';
				do
				{
					cin >> searchchoice;
				}
				while((searchchoice < 1) || (searchchoice > 3));
				if(hp[searchchoice] == 0)
				{
					cout << charname[searchchoice] << " is dead! \n";
				}
				else if(charclass[searchchoice] != 13)
				{
					cout << charname[searchchoice] << " is not able to wield this weapon! \n";
				}
				else
				{
					cout << charname[searchchoice] << " equips the legendary Excalibur! \n";
					ditemcheck[dungeonnum] = 0;
					weapon[searchchoice] = 3;
					i = searchchoice;
					statcalc();
				}
			}
			//15= Armor of Shadows	(Karas, Cavern of the Lost, Thief)
			else if(dungeonnum == 3)
			{
				cout << "and find the fabled Armor of Shadows, \n"
					 << "which only an Assassin can equip. \n"
					 << "Who among your party will attempt to wear the armor? \n"
					 << "1.) " << charname[1] << " the " << classname[charclass[1]] << '\n'
					 << "2.) " << charname[2] << " the " << classname[charclass[2]] << '\n'
					 << "3.) " << charname[3] << " the " << classname[charclass[3]] << '\n';
				do
				{
					cin >> searchchoice;
				}
				while((searchchoice < 1) || (searchchoice > 3));
				if(hp[searchchoice] == 0)
				{
					cout << charname[searchchoice] << " is dead! \n";
				}
				else if(charclass[searchchoice] != 13)
				{
					cout << charname[searchchoice] << " is not able to wear this armor! \n";
				}
				else
				{
					cout << charname[searchchoice] << " equips the fabled Armor of Shadows! \n";
					ditemcheck[dungeonnum] = 0;
					armor[searchchoice] = 15;
					i = searchchoice;
					statcalc();
				}
			}
			//15= Masamune			(Karas, Path of the Forgotten, Thief)
			else if(dungeonnum == 4)
			{
				cout << "and find the legendary Masamune, \n"
					 << "which only an Assassin can equip. \n"
					 << "Who among your party will attempt to wield this weapon? \n"
					 << "1.) " << charname[1] << " the " << classname[charclass[1]] << '\n'
					 << "2.) " << charname[2] << " the " << classname[charclass[2]] << '\n'
					 << "3.) " << charname[3] << " the " << classname[charclass[3]] << '\n';
				do
				{
					cin >> searchchoice;
				}
				while((searchchoice < 1) || (searchchoice > 3));
				if(hp[searchchoice] == 0)
				{
					cout << charname[searchchoice] << " is dead! \n";
				}
				else if(charclass[searchchoice] != 13)
				{
					cout << charname[searchchoice] << " is not able to wield this weapon! \n";
				}
				else
				{
					cout << charname[searchchoice] << " equips the legendary Masamune! \n";
					ditemcheck[dungeonnum] = 0;
					weapon[searchchoice] = 15;
					i = searchchoice;
					statcalc();
				}
			}
			//9 = Platinum Armor	(Briex, Halls of the Dead, Cleric)
			else if(dungeonnum == 5)
			{
				cout << "and find the fabled Platinum Armor, \n"
					 << "which only a High Priest can equip. \n"
					 << "Who among your party will attempt to wear the armor? \n"
					 << "1.) " << charname[1] << " the " << classname[charclass[1]] << '\n'
					 << "2.) " << charname[2] << " the " << classname[charclass[2]] << '\n'
					 << "3.) " << charname[3] << " the " << classname[charclass[3]] << '\n';
				do
				{
					cin >> searchchoice;
				}
				while((searchchoice < 1) || (searchchoice > 3));
				if(hp[searchchoice] == 0)
				{
					cout << charname[searchchoice] << " is dead! \n";
				}
				else if(charclass[searchchoice] != 13)
				{
					cout << charname[searchchoice] << " is not able to wear this armor! \n";
				}
				else
				{
					cout << charname[searchchoice] << " equips the fabled Platinum Armor! \n";
					ditemcheck[dungeonnum] = 0;
					armor[searchchoice] = 9;
					i = searchchoice;
					statcalc();
				}
			}
			//9 = Skull Crusher		(Briex, Gateway to the Netherworld, Cleric)
			else if(dungeonnum == 6)
			{
				cout << "and find the legendary Skull Crusher, \n"
					 << "which only a High Priest can equip. \n"
					 << "Who among your party will attempt to wield this weapon? \n"
					 << "1.) " << charname[1] << " the " << classname[charclass[1]] << '\n'
					 << "2.) " << charname[2] << " the " << classname[charclass[2]] << '\n'
					 << "3.) " << charname[3] << " the " << classname[charclass[3]] << '\n';
				do
				{
					cin >> searchchoice;
				}
				while((searchchoice < 1) || (searchchoice > 3));
				if(hp[searchchoice] == 0)
				{
					cout << charname[searchchoice] << " is dead! \n";
				}
				else if(charclass[searchchoice] != 13)
				{
					cout << charname[searchchoice] << " is not able to wield this weapon! \n";
				}
				else
				{
					cout << charname[searchchoice] << " equips the legendary Skull Crusher! \n";
					ditemcheck[dungeonnum] = 0;
					weapon[searchchoice] = 9;
					i = searchchoice;
					statcalc();
				}
			}
			//18= Mythril Mesh		(Lille, Boundless Desert, Dark Mage)
			else if(dungeonnum == 7)
			{
				cout << "and find the fabled Mythril Mesh, \n"
					 << "which only a Necromancer can equip. \n"
					 << "Who among your party will attempt to wear the armor? \n"
					 << "1.) " << charname[1] << " the " << classname[charclass[1]] << '\n'
					 << "2.) " << charname[2] << " the " << classname[charclass[2]] << '\n'
					 << "3.) " << charname[3] << " the " << classname[charclass[3]] << '\n';
				do
				{
					cin >> searchchoice;
				}
				while((searchchoice < 1) || (searchchoice > 3));
				if(hp[searchchoice] == 0)
				{
					cout << charname[searchchoice] << " is dead! \n";
				}
				else if(charclass[searchchoice] != 13)
				{
					cout << charname[searchchoice] << " is not able to wear this armor! \n";
				}
				else
				{
					cout << charname[searchchoice] << " equips the fabled Mythril Mesh! \n";
					ditemcheck[dungeonnum] = 0;
					armor[searchchoice] = 18;
					i = searchchoice;
					statcalc();
				}
			}
			//18= Death Scythe		(Lille, Tomb of Tslor, Dark Mage)
			else if(dungeonnum == 8)
			{
				cout << "and find the legendary Death Scythe, \n"
					 << "which only a Necromancer can equip. \n"
					 << "Who among your party will attempt to wield this weapon? \n"
					 << "1.) " << charname[1] << " the " << classname[charclass[1]] << '\n'
					 << "2.) " << charname[2] << " the " << classname[charclass[2]] << '\n'
					 << "3.) " << charname[3] << " the " << classname[charclass[3]] << '\n';
				do
				{
					cin >> searchchoice;
				}
				while((searchchoice < 1) || (searchchoice > 3));
				if(hp[searchchoice] == 0)
				{
					cout << charname[searchchoice] << " is dead! \n";
				}
				else if(charclass[searchchoice] != 13)
				{
					cout << charname[searchchoice] << " is not able to wield this weapon! \n";
				}
				else
				{
					cout << charname[searchchoice] << " equips the legendary Death Scythe! \n";
					ditemcheck[dungeonnum] = 0;
					weapon[searchchoice] = 18;
					i = searchchoice;
					statcalc();
				}
			}
			//12= Minazuki			(Ulm, East Trails, Monk)
			else if(dungeonnum == 9)
			{
				cout << "and find the fabled Minazuki, \n"
					 << "which only a Master can equip. \n"
					 << "Who among your party will attempt to wear the armor? \n"
					 << "1.) " << charname[1] << " the " << classname[charclass[1]] << '\n'
					 << "2.) " << charname[2] << " the " << classname[charclass[2]] << '\n'
					 << "3.) " << charname[3] << " the " << classname[charclass[3]] << '\n';
				do
				{
					cin >> searchchoice;
				}
				while((searchchoice < 1) || (searchchoice > 3));
				if(hp[searchchoice] == 0)
				{
					cout << charname[searchchoice] << " is dead! \n";
				}
				else if(charclass[searchchoice] != 13)
				{
					cout << charname[searchchoice] << " is not able to wear this armor! \n";
				}
				else
				{
					cout << charname[searchchoice] << " equips the fabled Minazuki! \n";
					ditemcheck[dungeonnum] = 0;
					armor[searchchoice] = 12;
					i = searchchoice;
					statcalc();
				}
			}
			//12= Gloves of War		(Ulm, Mountainside, Monk)
			else if(dungeonnum == 10)
			{
				cout << "and find the legendary Gloves of War, \n"
					 << "which only a Master can equip. \n"
					 << "Who among your party will attempt to wield this weapon? \n"
					 << "1.) " << charname[1] << " the " << classname[charclass[1]] << '\n'
					 << "2.) " << charname[2] << " the " << classname[charclass[2]] << '\n'
					 << "3.) " << charname[3] << " the " << classname[charclass[3]] << '\n';
				do
				{
					cin >> searchchoice;
				}
				while((searchchoice < 1) || (searchchoice > 3));
				if(hp[searchchoice] == 0)
				{
					cout << charname[searchchoice] << " is dead! \n";
				}
				else if(charclass[searchchoice] != 13)
				{
					cout << charname[searchchoice] << " is not able to wield this weapon! \n";
				}
				else
				{
					cout << charname[searchchoice] << " equips the legendary Gloves of War! \n";
					ditemcheck[dungeonnum] = 0;
					weapon[searchchoice] = 12;
					i = searchchoice;
					statcalc();
				}
			}
			//6 = Dragonscale Armor	(Trevia, Forest of Darkness, Acolyte)
			else if(dungeonnum == 11)
			{
				cout << "and find the fabled Dragonscale Armor, \n"
					 << "which only a Druid can equip. \n"
					 << "Who among your party will attempt to wear the armor? \n"
					 << "1.) " << charname[1] << " the " << classname[charclass[1]] << '\n'
					 << "2.) " << charname[2] << " the " << classname[charclass[2]] << '\n'
					 << "3.) " << charname[3] << " the " << classname[charclass[3]] << '\n';
				do
				{
					cin >> searchchoice;
				}
				while((searchchoice < 1) || (searchchoice > 3));
				if(hp[searchchoice] == 0)
				{
					cout << charname[searchchoice] << " is dead! \n";
				}
				else if(charclass[searchchoice] != 13)
				{
					cout << charname[searchchoice] << " is not able to wear this armor! \n";
				}
				else
				{
					cout << charname[searchchoice] << " equips the fabled Dragonscale Armor! \n";
					ditemcheck[dungeonnum] = 0;
					armor[searchchoice] = 6;
					i = searchchoice;
					statcalc();
				}
			}
			//6 = Wind Spear		(Trevia, Field of Death, Acolyte)
			else if(dungeonnum == 12)
			{
				cout << "and find the legendary Wind Spear, \n"
					 << "which only a Druid can equip. \n"
					 << "Who among your party will attempt to wield this weapon? \n"
					 << "1.) " << charname[1] << " the " << classname[charclass[1]] << '\n'
					 << "2.) " << charname[2] << " the " << classname[charclass[2]] << '\n'
					 << "3.) " << charname[3] << " the " << classname[charclass[3]] << '\n';
				do
				{
					cin >> searchchoice;
				}
				while((searchchoice < 1) || (searchchoice > 3));
				if(hp[searchchoice] == 0)
				{
					cout << charname[searchchoice] << " is dead! \n";
				}
				else if(charclass[searchchoice] != 13)
				{
					cout << charname[searchchoice] << " is not able to wield this weapon! \n";
				}
				else
				{
					cout << charname[searchchoice] << " equips the legendary Wind Spear! \n";
					ditemcheck[dungeonnum] = 0;
					weapon[searchchoice] = 6;
					i = searchchoice;
					statcalc();
				}
			}
		}
		else
		{
			cout << "but you don't find anyting useful. \n";
		}
	}
	else if((dungeonx == dspecialx[dungeonnum]) && (dungeony == dspecialy[dungeonnum]))
	{
		//Special Check
		if(dspecialcheck[dungeonnum] != 0)
		{
			//Key
			if(dungeonnum % 2 == 1)
			{
				//Dungeon numbers 1, 3, 5, 7, 9, 11
				//Key numbers     1, 2, 3, 4, 5, 6
				cout << "and you find a key that will allow you to enter the next area. \n";
				key[((dungeonnum + 1) / 2)] = 1;
				dspecialcheck[dungeonnum] = 0;
			}
			//Boss
			else
			{
				cout << "and you stumble upon the dungeon ruler! \n";
				cout << "Press one to continue: ";
				cin >> one;
				bosscheck = 1;
				battle();
			}
		}
		else
		{
			cout << "but you don't find anyting useful. \n";
		}
	}
	else
	{
		cout << "but you don't find anyting useful. \n";
	}
	cout << "Press one to continue: ";
	cin >> one;
	system("CLS");
}

void healmagicuse()
{
	system("CLS");
	cout << "-------------------------------------------------------------------------------\n"
	     << "|" << setw(12) << "Character: " << setw(21) << charname[1] << setw(21) << charname[2] << setw(21) << charname[3] << setw(3) << "|" << '\n'
		 << "|" << setw(12) << "HP: " << setw(17) << hp[1] << "/" << setw(3) << uchpmax[1] << setw(17) << hp[2] << "/" << setw(3) << uchpmax[2] << setw(17) << hp[3] << "/" << setw(3) << uchpmax[3]<< setw(3) << "|" << '\n'
		 << "|" << setw(12) << "MP: " << setw(17) << mp[1] << "/" << setw(3) << ucmpmax[1] << setw(17) << mp[2] << "/" << setw(3) << ucmpmax[2] << setw(17) << mp[3] << "/" << setw(3) << ucmpmax[3]<< setw(3) << "|" << '\n'
		 << "-------------------------------------------------------------------------------\n";
	cout << "Select a character to use magic: \n"
		 << "1.) " << charname[1] << '\n'
		 << "2.) " << charname[2] << '\n'
		 << "3.) " << charname[3] << '\n';
	do
	{
		cin >> choice;
	}
	while((choice < 1) || (choice > 3));
	if(hp[choice] == 0)
	{
		cout << charname[choice] << " is dead! \n";
	}
	//some problems with else if below, changed to test, if it works, I will keep it this way
	//classes that can use healing magic:         3               8  9             13  14  15
	//classes that can't use healing magic: 1   2   4   5   6   7      10  11  12             16  17  18
	//backwards way of testing who can use magic, check those who can't first, then all else can use magic
	else if((charclass[choice]) == 1)
	{
		cout << charname[choice] << " is unable to use healing magic. \n";
	}
	else if((charclass[choice]) == 2)
	{
		cout << charname[choice] << " is unable to use healing magic. \n";
	}
	else if((charclass[choice]) == 4) 
	{
		cout << charname[choice] << " is unable to use healing magic. \n";
	}
	else if((charclass[choice]) == 5) 
	{
		cout << charname[choice] << " is unable to use healing magic. \n";
	}
	else if((charclass[choice]) == 6) 
	{
		cout << charname[choice] << " is unable to use healing magic. \n";
	}
	else if((charclass[choice]) == 7)
	{
		cout << charname[choice] << " is unable to use healing magic. \n";
	}
	else if((charclass[choice]) == 10)
	{
		cout << charname[choice] << " is unable to use healing magic. \n";
	}
	else if((charclass[choice]) == 11)
	{
		cout << charname[choice] << " is unable to use healing magic. \n";
	}
	else if((charclass[choice]) == 12) 
	{
		cout << charname[choice] << " is unable to use healing magic. \n";
	}
	else if((charclass[choice]) == 16)
	{
		cout << charname[choice] << " is unable to use healing magic. \n";
	}
	else if((charclass[choice]) == 17)
	{
		cout << charname[choice] << " is unable to use healing magic. \n";
	}
	else if((charclass[choice]) == 18) 
	{
		cout << charname[choice] << " is unable to use healing magic. \n";
	}
	else
	{
		cout << "Select the magic spell you wish to cast: \n"
			 << " 0.) Cancel \n";
		//Fighter and Acolyte Magic Use
		if((charclass[choice] == 13) || (charclass[choice] == 8) || (charclass[choice] == 14))
		{
			cout << " 1.) Heal I          3 MP \n";
			if(charclass[choice] == 14)
			{
				cout << " 2.) Heal II         6 MP \n";
			}
			do
			{
				cin >> spellchoice;
			}
			while((spellchoice < 0) || (spellchoice > 2));
			if(spellchoice == 1)
			{
				spellnum = 1;
			}
			else if((spellchoice == 2) && (charclass[choice] == 14))
			{
				spellnum = 9;
			}
			else
			{
				spellnum = 0;
			}
		}
		//Cleric Magic Use
		else if(((charclass[choice]) == 15) || (charclass[choice] == 9) || (charclass[choice] == 3))
		{
			cout << " 1.) Heal I          3 MP \n"
				 << " 2.) Resurrect I    20 MP \n";
			if((charclass[choice] == 15) || (charclass[choice] == 9))
			{
				cout << " 3.) Heal II         6 MP \n"
					 << " 4.) Resurrect I I  30 MP \n";
			}
			if(charclass[choice] == 15)
			{
				cout << " 5.) Heal III       12 MP \n"
					 << " 6.) Resurrect III  40 MP \n";
			}
			do
			{
				cin >> spellchoice;
			}
			while((spellchoice < 0) || (spellchoice > 6));
			if(spellchoice == 1)
			{
				spellnum = 1;
			}
			else if(spellchoice == 2)
			{
				spellnum = 4;
			}
			else if((spellchoice == 3) && ((charclass[choice] == 9) || (charclass[choice] == 15)))
			{
				spellnum = 9;
			}
			else if((spellchoice == 4) && ((charclass[choice] == 9) || (charclass[choice] == 15)))
			{
				spellnum = 12;
			}
			else if((spellchoice == 5) && (charclass[choice] == 15))
			{
				spellnum = 17;
			}
			else if((spellchoice == 6) && (charclass[choice] == 15))
			{
				spellnum = 20;
			}
			else
			{
				spellnum = 0;
			}
		}
		if(spellnum != 0)
		{
			//Target Select
			cout << "Select a Target: \n"
				 << "1) " << charname[1] << '\n'
				 << "2) " << charname[2] << '\n'
				 << "3) " << charname[3] << '\n';
			do
			{
				cin >> target;
			}
			while((target < 1) || (target > 3));
			//Spell Effects			
			//Heal I
			if((spellnum == 1) && ((mp[choice]) >= 3))
			{
				if(hp[target] != 0)
				{
					damage = (((ucmatp[choice]) + (uematp[choice])) * .75);
					hp[target] = hp[target] + damage;
					mp[choice] = mp[choice] - 3;
					if((hp[target]) > (uchpmax[target]))
					{
						hp[target] = uchpmax[target];
					}
					cout << charname[choice] << " casts Heal I. " << charname[target] << " is healed for " << damage << " HP. \n";	
				}
				else
				{
					cout << charname[target] << " is dead! \n";
					turn = 0;
				}
			}		
			//Heal II
			else if((spellnum == 9) && ((mp[sequence[i]]) >= 6))
			{
				if(hp[target] != 0)
				{
					damage = (((ucmatp[choice]) + (uematp[choice])) * 1.25);
					hp[target] = hp[target] + damage;
					mp[choice] = mp[choice] - 6;
					if((hp[target]) > (uchpmax[target]))
					{
						hp[target] = uchpmax[target];
					}
					cout << charname[choice] << " casts Heal II. " << charname[target] << " is healed for " << damage << " HP. \n";
				}
				else
				{
					cout << charname[target] << " is dead! \n";
					turn = 0;
				}
			}
			//Heal III
			else if((spellnum == 17) && ((mp[choice]) >= 12))
			{
				if(hp[target] != 0)
				{
					hp[target] = uchpmax[target];
					mp[choice] = mp[choice] - 12;
					cout << charname[choice] << " casts Heal III. " << charname[target] << " is fully healed. \n";	
				}
				else
				{
					cout << charname[target] << " is dead! \n";
					turn = 0;
				}
			}
			//Resurrect I
			else if((spellnum == 4) && ((mp[choice]) >= 20))
			{
				if(hp[target] == 0)
				{
					hp[target] = 1;
					mp[choice] = mp[choice] - 20;
					cremain = cremain + 1;
					cout << charname[choice] << " casts Resurrect I. " << charname[target] << " is revived. \n";
				}
				else
				{
					cout << charname[target] << " is not dead! \n";
					turn = 0;
				}
			}
			//Resurrect II
			else if((spellnum == 12) && ((mp[choice]) >= 30))
			{
				if(hp[target] == 0)
				{
					hp[target] = (uchpmax[target] * .5);
					mp[choice] = mp[choice] - 30;
					cremain = cremain + 1;
					cout << charname[choice] << " casts Resurrect II. " << charname[target] << " is revived. \n";
				}
				else
				{
					cout << charname[target] << " is not dead! \n";
					turn = 0;
				}
			}
			//Resurrect III
			else if((spellnum == 20) && ((mp[choice]) >= 40))
			{
				if(hp[target] == 0)
				{
					hp[target] = uchpmax[target];
					mp[choice] = mp[choice] - 40;
					cremain = cremain + 1;
					cout << charname[choice] << " casts Resurrect III. " << charname[target] << " is revived. \n";
				}
				else
				{
					cout << charname[target] << " is not dead! \n";
					turn = 0;
				}
			}
		}
	}
	cout << "Press one to continue: ";
	cin >> one;
	system("CLS");
}

//Dungeons
void MallowMarsh()
{
	system("CLS");
	cout << "You have entered Mallow Marsh. \n";
	dungeonnum = 1;
	dungeonx = dexitx[dungeonnum];
	dungeony = dexity[dungeonnum];
	step = 0;
	dexitcheck = 0;
	cout << "Press 1 to continue ";
	cin >> one;
	dungeonmain();
}

void HiddenEverglades()
{
	system("CLS");
	cout << "You have entered the Hidden Everglades. \n";
	dungeonnum = 2;
	dungeonx = dexitx[dungeonnum];
	dungeony = dexity[dungeonnum];
	step = 0;
	dexitcheck = 0;
	cout << "Press 1 to continue ";
	cin >> one;
	dungeonmain();
}

void PathoftheForgotten()
{
	system("CLS");
	cout << "You have entered the Path of the Forgotten. \n";
	dungeonnum = 3;
	dungeonx = dexitx[dungeonnum];
	dungeony = dexity[dungeonnum];
	step = 0;
	dexitcheck = 0;
	cout << "Press 1 to continue ";
	cin >> one;
	dungeonmain();
}

void CavernoftheLost()
{
	system("CLS");
	cout << "You have entered the Cavern of the Lost. \n";
	dungeonnum = 4;
	dungeonx = dexitx[dungeonnum];
	dungeony = dexity[dungeonnum];
	step = 0;
	dexitcheck = 0;
	cout << "Press 1 to continue ";
	cin >> one;
	dungeonmain();
}

void HallsoftheDead()
{
	system("CLS");
	cout << "You have entered the Halls of the Dead. \n";
	dungeonnum = 5;
	dungeonx = dexitx[dungeonnum];
	dungeony = dexity[dungeonnum];
	step = 0;
	dexitcheck = 0;
	cout << "Press 1 to continue ";
	cin >> one;
	dungeonmain();
}

void GatewaytotheNW()
{
	system("CLS");
	cout << "You have entered the Gateway to the Netherworld. \n";
	dungeonnum = 6;
	dungeonx = dexitx[dungeonnum];
	dungeony = dexity[dungeonnum];
	step = 0;
	dexitcheck = 0;
	cout << "Press 1 to continue ";
	cin >> one;
	dungeonmain();
}

void BoundlessDesert()
{
	system("CLS");
	cout << "You have entered the Boundless Desert. \n";
	dungeonnum = 7;
	dungeonx = dexitx[dungeonnum];
	dungeony = dexity[dungeonnum];
	step = 0;
	dexitcheck = 0;
	cout << "Press 1 to continue ";
	cin >> one;
	dungeonmain();
}

void TombofTslor()
{
	system("CLS");
	cout << "You have entered Tomb of Tslor. \n";
	dungeonnum = 8;
	dungeonx = dexitx[dungeonnum];
	dungeony = dexity[dungeonnum];
	step = 0;
	dexitcheck = 0;
	cout << "Press 1 to continue ";
	cin >> one;
	dungeonmain();
}

void EastTrails()
{
	system("CLS");
	cout << "You have entered the East Trails. \n";
	dungeonnum = 9;
	dungeonx = dexitx[dungeonnum];
	dungeony = dexity[dungeonnum];
	step = 0;
	dexitcheck = 0;
	cout << "Press 1 to continue ";
	cin >> one;
	dungeonmain();
}

void Mountainside()
{
	system("CLS");
	cout << "You have entered the Mountainside. \n";
	dungeonnum = 10;
	dungeonx = dexitx[dungeonnum];
	dungeony = dexity[dungeonnum];
	step = 0;
	dexitcheck = 0;
	cout << "Press 1 to continue ";
	cin >> one;
	dungeonmain();
}

void ForestofDarkness()
{
	system("CLS");
	cout << "You have entered the Forest of Darkness. \n";
	dungeonnum = 11;
	dungeonx = dexitx[dungeonnum];
	dungeony = dexity[dungeonnum];
	step = 0;
	dexitcheck = 0;
	cout << "Press 1 to continue ";
	cin >> one;
	dungeonmain();
}

void FieldofDeath()
{
	system("CLS");
	cout << "You have entered the Field of Death. \n";
	dungeonnum = 12;
	dungeonx = dexitx[dungeonnum];
	dungeony = dexity[dungeonnum];
	step = 0;
	dexitcheck = 0;
	cout << "Press 1 to continue ";
	cin >> one;
	dungeonmain();
}



void emagic()
{
	//Enemy Magic
	x = rand() % 4;
	//Light Spells
	if(x == 0)
	{
		//Light III
		if(((televel[sequence[i]]) > 20) && ((temp[sequence[i]]) >= 16))
		{
			damage = (((tematp[sequence[i]]) * 1.75) - ((ucmdfp[target] + uemdfp[target]) / 2));
			if(damage < 0)
			{
				damage = 0;
			}
			temp[sequence[i]] = temp[sequence[i]] - 16;
			cout << tename[sequence[i]] << " casts Light III. " << charname[target] << " is damaged for " << damage << " HP. \n"; 
		}
		//Light II
		else if(((televel[sequence[i]]) > 20) && ((temp[sequence[i]]) >= 8))
		{
			damage = (((tematp[sequence[i]]) * 1.25) - ((ucmdfp[target] + uemdfp[target]) / 2));
			if(damage < 0)
			{
				damage = 0;
			}
			temp[sequence[i]] = temp[sequence[i]] - 8;
			cout << tename[sequence[i]] << " casts Light II. " << charname[target] << " is damaged for " << damage << " HP. \n";
		}
		//Light I
		else if(((televel[sequence[i]]) > 0) && ((temp[sequence[i]]) >= 4))
		{
			damage = (((tematp[sequence[i]]) * .75) - ((ucmdfp[target] + uemdfp[target]) / 2));
			if(damage < 0)
			{
				damage = 0;
			}
			temp[sequence[i]] = temp[sequence[i]] - 4;
			cout << tename[sequence[i]] << " casts Light I. " << charname[target] << " is damaged for " << damage << " HP. \n";
		}
		//No MP
		else
		{
			cout << tename[sequence[i]] << " does not have enough MP. \n";
			damage = 0;
		}
	}
	//Fire Spells
	else if(x == 1)
	{
		//Fire III
		if(((televel[sequence[i]]) > 20) && ((temp[sequence[i]]) >= 10))
		{
			damage = (((tematp[sequence[i]]) * 1.5) - ((ucmdfp[target] + uemdfp[target]) / 2));
			if(damage < 0)
			{
				damage = 0;
			}
			temp[sequence[i]] = temp[sequence[i]] - 10;
			cout << tename[sequence[i]] << " casts Fire III. " << charname[target] << " is damaged for " << damage << " HP. \n"; 
		}
		//Fire II
		else if(((televel[sequence[i]]) > 20) && ((temp[sequence[i]]) >= 5))
		{
			damage = (((tematp[sequence[i]]) * 1) - ((ucmdfp[target] + uemdfp[target]) / 2));
			if(damage < 0)
			{
				damage = 0;
			}
			temp[sequence[i]] = temp[sequence[i]] - 5;
			cout << tename[sequence[i]] << " casts Fire II. " << charname[target] << " is damaged for " << damage << " HP. \n";
		}
		//Fire I
		else if(((televel[sequence[i]]) > 0) && ((temp[sequence[i]]) >= 2))
		{
			damage = (((tematp[sequence[i]]) * .5) - ((ucmdfp[target] + uemdfp[target]) / 2));
			if(damage < 0)
			{
				damage = 0;
			}
			temp[sequence[i]] = temp[sequence[i]] - 2;
			cout << tename[sequence[i]] << " casts Fire I. " << charname[target] << " is damaged for " << damage << " HP. \n";
		}
		//No MP
		else
		{
			cout << tename[sequence[i]] << " does not have enough MP. \n";
			damage = 0;
		}
	}
	//Ice Spells
	else if(x == 2)
	{
		//Ice III
		if(((televel[sequence[i]]) > 20) && ((temp[sequence[i]]) >= 12))
		{
			damage = (((tematp[sequence[i]]) * 1.75) - ((ucmdfp[target] + uemdfp[target]) / 2));
			if(damage < 0)
			{
				damage = 0;
			}
			temp[sequence[i]] = temp[sequence[i]] - 12;
			cout << tename[sequence[i]] << " casts Ice III. " << charname[target] << " is damaged for " << damage << " HP. \n"; 
		}
		//Ice II
		else if(((televel[sequence[i]]) > 20) && ((temp[sequence[i]]) >= 6))
		{
			damage = (((tematp[sequence[i]]) * 1.25) - ((ucmdfp[target] + uemdfp[target]) / 2));
			if(damage < 0)
			{
				damage = 0;
			}
			temp[sequence[i]] = temp[sequence[i]] - 6;
			cout << tename[sequence[i]] << " casts Ice II. " << charname[target] << " is damaged for " << damage << " HP. \n";
		}
		//Ice I
		else if(((televel[sequence[i]]) > 0) && ((temp[sequence[i]]) >= 3))
		{
			damage = (((tematp[sequence[i]]) * .75) - ((ucmdfp[target] + uemdfp[target]) / 2));
			if(damage < 0)
			{
				damage = 0;
			}
			temp[sequence[i]] = temp[sequence[i]] - 3;
			cout << tename[sequence[i]] << " casts Ice I. " << charname[target] << " is damaged for " << damage << " HP. \n";
		}
		//No MP
		else
		{
			cout << tename[sequence[i]] << " does not have enough MP. \n";
			damage = 0;
		}
	}
	//Black Hole Spells
	else if(x == 3)
	{
		//Black Hole III
		if(((televel[sequence[i]]) > 20) && ((temp[sequence[i]]) >= 25))
		{
			hp[target] = 1;
			damage = 0;
			temp[sequence[i]] = temp[sequence[i]] - 25;
			cout << tename[sequence[i]] << " casts Black Hole III. " << charname[target] << "'s life is drained. \n"; 
		}
		//Black Hole II
		else if(((televel[sequence[i]]) > 20) && ((temp[sequence[i]]) >= 15))
		{
			hp[target] = (hp[target] * .25);
			damage = 0;
			temp[sequence[i]] = temp[sequence[i]] - 15;
			cout << tename[sequence[i]] << " casts Black Hole II. " << charname[target] << "'s life is drained. \n";
		}
		//Black Hole I
		else if(((televel[sequence[i]]) > 0) && ((temp[sequence[i]]) >= 10))
		{
			hp[target] = (hp[target] * .5);
			damage = 0;
			temp[sequence[i]] = temp[sequence[i]] - 10;
			cout << tename[sequence[i]] << " casts Black Hole I. " << charname[target] << "'s life is drained. \n";
		}
		//No MP
		else
		{
			cout << tename[sequence[i]] << " does not have enough MP. \n";
			damage = 0;
		}
	}
	hp[target] = hp[target] - damage;
	if(hp[target] < 0)
	{
		cout << charname[target] << " is slain. \n";
		hp[target] = 0;
		cremain = cremain - 1;
		if(cremain == 0)
		{
			//for-loop forced end
			i = enemycount + 2;
		}
	}
}