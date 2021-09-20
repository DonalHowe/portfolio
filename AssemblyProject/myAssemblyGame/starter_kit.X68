*-------------------------------------------------------
* Starting memory address for the programme $1000
*-------------------------------------------------------
    
    org $1000

*-------------------------------------------------------
*Choose to be a Plumber or a Rabbit 
*-------------------------------------------------------

*-------------------------------------------------------
*Validation values to be used, modify as needed
*Add additional validation values as required
*-------------------------------------------------------
exit        EQU 0      used to exit assembly program
min_potions EQU 1      min number of potions
max_potions EQU 9      max number of potions
min_weapons EQU 1      min weapons
max_weapons EQU 3      max weapons
win_point   EQU 5      points accumilated on win
lose_point  EQU 8      points deducted on a loss
collison_value EQU 6
mine_loc    EQU 100    used below for some simple collision detection using CMP
                       * example for a hit
Player_health EQU 10
Enemy_health EQU 5
Attack_value EQU 5
Heal_Value   EQU 3
super_damage EQU 10
Boss_health EQU 15

*Start of Game
start:
   * move.b  #100,$4000 put score/health in memory location $4000
    *lea     $4000,A3   assign address A3 to that memory location
    
    move.b  #Player_health,$4020 put score/health in memory location $4000
    lea     $4020,A2   assign address A3 to that memory location
    
    move.b  #Enemy_health,$4010 put score/health in memory location $4000
    lea     $4010,A5   assign address A3 to that memory location
     move.b  #Boss_health ,$4040 put score/health in memory location $4000
    lea     $4040,A7   assign address A3 to that memory location

   

    bsr     welcome    branch to the welcome subroutine
    bsr     input      branch to the input subroutine
    bsr     game       branch to the game subroutine
*Game loop
    org     $3000      the rest of the program is to be located from 3000 onwards

*-------------------------------------------------------
*-------------------Game Subroutine---------------------
*-------------------------------------------------------
game:
    bsr     gameloop   branch to gameloop subroutine
    rts                return from game: subroutine
          
end:
    simhalt

*-------------------------------------------------------
*-------------------Welcome Subroutine------------------
*-------------------------------------------------------
welcome:
    bsr     endl            branch to endl subroutine
    lea     welcome_msg,A1  assign message to address register A1
    move.b  #14,D0          move literal 14 to DO
    trap    #15             trap and interpret value in D0
    bsr     endl            branch to endl subroutine
    rts                     return from welcome: subroutine

*-------------------------------------------------------
*---------Gameplay Input Values Subroutine--------------
*-------------------------------------------------------    
input:
    bsr     potions         branch to potion input subroutine
    bsr     weapons         branch to weaponss input subroutine
    rts

*-------------------------------------------------------
*----------------Gameloop (main loop)-------------------
*------------------------------------------------------- 
gameloop:
    bsr     update          branch to update game subroutine 
    bsr     clear_screen    clears the screen       
     
  *  bsr     draw            branch to draw screen subroutine
    bsr     clear_screen    clears the screen
  *  bsr     gameplay        branch to gameplay subroutine
    bsr     RoomOne
    *bsr     clear_screen    clears the screen
    
    *bsr     hud             branch to display HUD subroutine
    *bsr     clear_screen    clears the screen
   * bsr     replay          branch to replay game subroutine
    *bsr     clear_screen    clears the screen
    rts                     return from gameloop: subroutine

*-------------------------------------------------------
*----------------Update Quest Progress------------------
*  Complete Quest
*------------------------------------------------------- 
update:
    bsr     endl            print a CR and LF
    bsr     decorate        decorate with dots using a loop
    lea     update_msg,A1   
    move.b  #14,D0
    trap    #15
    bsr     decorate
    rts
*-------------------------------------------------------
*-----------------Draw Quest Updates--------------------
* Draw the game progress information, status regarding
* quest
*------------------------------------------------------- 
draw:
    bsr     endl
    bsr     decorate
    lea     draw_msg,A1
    move.b  #14,D0
    trap    #15
    bsr     decorate
    rts

*-------------------------------------------------------
*--------------------Potions Inventory---------------------
* Number of potions to be used in a Quest 
*------------------------------------------------------- 
potions:
    bsr     endl
    bsr     decorate
    lea     potions_msg,A1
    move.b  #14,D0
    trap    #15
    move.b  #4,D0
    trap    #15
    bsr     decorate
    rts

*-------------------------------------------------------
*-------------------------Weapons-----------------------
* Number of weapons
*-------------------------------------------------------   
weapons:
    bsr     endl
    bsr     decorate
    lea     weapons_msg,A1
    move.b  #14,D0
    trap    #15
    move.b  #4,D0
    trap    #15
  
    bsr     decorate
    rts
        
GunChoice: 
                lea    weapnChoiceGun_msg ,A1
                move.b  #14,D0
                trap    #15
                bsr RoomOneAttack

FireChoice:
                lea    weapnChoicefire_msg,A1
                move.b  #14,D0
                trap    #15
                bsr RoomOneAttack
                
           
SwordChoice:
                lea    weapnChoiceSword,A1

                move.b  #14,D0
                trap    #15
                bsr RoomOneAttack
ultChoice:
        
                lea    super_msg,A1

                move.b  #14,D0
                trap    #15
                bsr RoomTwoAttack
                
                
                      
GunChoiceTwo: 
                lea    weapnChoiceGun_msg ,A1
                move.b  #14,D0
                trap    #15
                bsr BossRoomPtTwo

FireChoiceTwo:
                lea    weapnChoicefire_msg,A1
                move.b  #14,D0
                trap    #15
                bsr BossRoomPtTwo
                
           

ultChoiceTwo:
        
                lea    super_msg,A1

                move.b  #14,D0
                trap    #15
                bsr BossRoomPtTwo

*-------------------------------------------------------
*---heal playewr--------------------------
*------------------------------------------------------- 
playerHeal:
 move.b $4020,D0
    *moves attackValue to d0
    move.b #Heal_Value ,D3
    *subtrackts attack value from player health
    add.b  D3,D0
    
    move.b D0,$4020
    lea   $4020,A6
    move.b $4020,D1
    bsr     endl
    
    lea    playerSelfHeal,A1
    move    #14,D0
    trap    #15

    Move #3,D0
    Trap #15
    bsr     endl
    lea bossRoomBeforeEnter,A1
    move.b #14,D0
    trap    #15
    move.b #4,D0
    trap    #15

    
    bsr bossRoom
*-------------------------------------------------------
*---Game Play (Quest Progress)--------------------------
*------------------------------------------------------- 
gameplay:
    bsr     endl
    bsr     decorate
    *lea     gameplay_msg,A1
   * move.b  #14,D0
    *trap    #15
  
    bsr     decorate
    *bsr     collision
    rts

*-------------------------------------------------------
*-----------------Heads Up Display (Score)--------------
* Retrieves the score from memory location
*-------------------------------------------------------   
hud:

    bsr     endl
    bsr     decorate
    lea     hud_msg,A1
    move.b  #14,D0
    trap    #15
    move.b  (A3),D1     retrieve the value A3 point to and move to D1
    move.b  #3,D0       move literal 3 to D0
    trap    #15         intrepret value in D0, which 3 which displays D1
    bsr     decorate
    rts

*-------------------------------------------------------
*-----------------------Being Attacked------------------
* This could be used for collision detection
*-------------------------------------------------------
collision:
    move.b  #mine_loc,D1
    cmp     #100,D1 is( x == 100)?
	bne     collision_miss if x is equal to 100, then hit
collision_hit:
    *hit
    bsr     endl
    lea     hit_msg,A1
    move    #14,D0
    trap    #15
       *moving enemy 
    move.b $4010,D0
    move.b #Attack_value,D3
    sub.b  D3,D0
    
    move.b D0,$4010
    lea   $4010,A5
    move.b $4010,D1
   
    lea    enemyHealthmsg,A1
    move    #14,D0
    trap    #15

    Move #3,D0
    Trap #15
    bsr RoomAttackWin
    
collision_miss:
    *miss
    lea     miss_msg,A1
    move    #14,D0
    trap    #15
    bsr RoomOneAttack
  



*-------------------------------------------------------
*--------------------------Loop-------------------------
*-------------------------------------------------------
loop:
    move.b  #5, D3 loop counter D3=5
next:
    lea     loop_msg,A1
    move.b  #14,D0
    trap    #15
	sub     #1,D3   decrement loop counter
    bne     next    repeat until D0=0


*-------------------------------------------------------
*--------------------------credits-------------------------
*-------------------------------------------------------
credits:
  
       
        bsr     endl
        bsr     endl
        bsr     endl
        bsr     endl
        lea credits_msg,A1
        move.b #14,D0
        trap #15

       bsr replay

*-------------------------------------------------------
*------------------Screen Decoration--------------------
*-------------------------------------------------------
decorate:
    move.b  #60, D3
    bsr     endl
out:
    lea     loop_msg,A1
    move.b  #14,D0
    trap    #15
	sub     #1,D3   decrement loop counter
    bne     out	    repeat until D0=0
    bsr     endl
    rts
    
clear_screen: 
    move.b  #11,D0      clear screen
    move.w  #$ff00,D1
    trap    #15
    rts
    
 *-------------------------------------------------------
*------------------------Room One-------------------------
*-------------------------------------------------------
RoomOne:
        bsr     endl
        bsr     decorate
        lea     RoomOnemsg,A1
        move.b  #14,D0
        trap    #15
        bsr     endl
        bsr     decorate
       
        *asking the player to choose the weapon
        lea     damagemsg,A1
        move.b  #14,D0
        trap    #15
        
        *the player now inputs
        move.b  #4,D0
        trap    #15
        move.b  D1,$4005
        lea $4005,A6
        
        *now we compare the value against the chosen weapon 4 FOR GUN 5 FOR FIRE
        CMP     #5,D1
        BLT     GunChoice
        BGT     FireChoice
        BEQ   SwordChoice
        
        
       
RoomOneAttack:       
        
         *now that weapon is selected we will shoot rabbid
        bsr     endl
        bsr     decorate    
        LEA  attackmsg,A1
        move.b  #14,D0
        trap    #15
        *NOW WE TAKE INPUT FROM THE PLKAYER TO ATTACK THE RABBID
        move.b  #4,D0
        trap    #15
       
        
        *NOW WE TAKE INPUT FROM THE PLKAYER TO hit THE RABBID

        CMP     #6,D1
        BGT     collision_hit
        BLT    collision_miss
RoomAttackWin:        
        bsr     endl
        LEA  endRoomOnemsg,A1
        move.b  #14,D0
        trap    #15
        bsr RoomTwo

RoomAttackLose:
        bsr     endl     
        bsr RoomOne

 *-------------------------------------------------------
*------------------------Room Two-------------------------
*-------------------------------------------------------
RoomTwo:
        bsr     endl
        bsr     decorate
        lea     roomTwo_Entermsg,A1
        move.b  #14,D0
        trap    #15
        move.b  #4,D0
        trap    #15
        bsr     endl
       *asking the player to choose the weapon
       lea     newPower_msg,A1
       move.b  #14,D0
       trap    #15
       bsr     endl 
       lea    ult_msg,A1
       move.b  #14,D0
       trap    #15
       bsr     endl
       move.b  #4,D0
       trap    #15
      
     
       *checks to see what weapon the player chooses
        CMP     #6,D1
        BLT     GunChoice
        BGT     FireChoice
        BEQ   ultChoice


       *the player now inputs
             
               
        
       
RoomTwoAttack:       
        
    *now we are going to do damage to teh player to force him to heal
    *moving the player health to d0
    move.b $4020,D0
    *moves attackValue to d0
    move.b #Attack_value,D3
    *subtrackts attack value from player health
    sub.b  D3,D0
    
    move.b D0,$4020
    lea   $4020,A6
    move.b $4020,D1
    bsr     endl

    lea    player_health_left,A1
    move.b  #14,D0
    trap    #15

*displays the players remaining health
    Move #3,D0
    Trap #15
heal:
    bsr endl
    lea player_heal_msg,A1
    move.b #14,D0
    trap #15
    
    *now we need to heal the player
    move.b  #4,D0
    trap    #15
    cmp     #1,D1
    BEQ     playerHeal
    BLT     heal
    BGT     heal
    
*-------------------------------------------------------
*------------------------Boss Room-------------------------
*-------------------------------------------------------
bossRoom:
         bsr     endl
         lea bossRoomIntro,A1
         move.b #14,D0
         trap  #15
         bsr     endl
         move.b #4,D0
         trap  #15
            
        CMP     #6,D1
        BLT     GunChoiceTwo
        BGT     FireChoiceTwo
        BEQ   ultChoiceTwo
        
BossRoomPtTwo:
            
     move.b $4040,D0
    *moves attackValue to d0
    move.b #Attack_value,D3
    *subtrackts attack value from player health
    sub.b  D3,D0
    
    move.b D0,$4040
    lea   $4040,A6
    move.b $4040,D1
    bsr     endl
    
    lea bossDamageTaken,A1
    move.b #14,D0
    trap  #15
    
    Move #3,D0
    Trap #15
    * want to repeat the boss damge
   
    move.b $4040,D0
    move.b #Attack_value,D3
    sub.b  D3,D0
    
    move.b D0,$4040
    lea   $4040,A6
    move.b $4040,D1

    cmp   #5,D1
    BEQ   BossRoomPtTwo  
    BLT   Ending

*-------------------------------------------------------
*--------------------------ending-------------------------
*-------------------------------------------------------

Ending:
         
        bsr     endl
        bsr     endl
        bsr     endl
        bsr     endl
        lea ending_msg,A1
        move.b #14,D0
        trap #15
        bsr credits



*-------------------------------------------------------
*------------------------Replay-------------------------
*-------------------------------------------------------
replay:
    bsr     endl
    lea     replay_msg,A1
    move.b  #14,D0
    trap    #15
    
    move.b  #4,D0
    trap    #15

    cmp     #exit,D1
    beq     end         if SR Z register contains 1 beq => Branch Equals
    bsr     gameloop

endl:
    movem.l D0/A1,-(A7)
    move    #14,D0
    lea     crlf,A1
    trap    #15
    movem.l (A7)+,D0/A1
    rts
    
*-------------------------------------------------------
*-------------------Data Delarations--------------------
*-------------------------------------------------------

crlf:           dc.b    $0D,$0A,0
welcome_msg:    dc.b    '************************************************************'
                dc.b    $0D,$0A
                dc.b    'The Great Plumbers Vs Rabbids'
                dc.b    $0D,$0A
                dc.b    '************************************************************'
                dc.b    $0D,$0A
                dc.b    '************************************************************'
                dc.b    $0D,$0A
                dc.b    'This a turn based strategy game where you the player'
                dc.b    $0D,$0A
                dc.b    'has to kill all of the rabbids before you die and if'
                dc.b    $0D,$0A
                dc.b    'you win you will get all of the sweet sweet loot'
                dc.b    $0D,$0A
                dc.b    '************************************************************'
                dc.b    $0D,$0A
potions_msg:    dc.b    'Number of potions : ',0
weapons_msg:    dc.b    'Each quest need at least 2 Weapons'
                dc.b    $0D,$0A
                dc.b    'Enter number for weapons : ',0
gameplay_msg:   dc.b    'Add Gameplay !',0
RoomOnemsg:     dc.b    'room one '
                dc.b    'kill the rabbid',0                
                dc.b    $0D,$0
weapnChoiceSword dc.b 'you have selected the sword ',0
                 dc.b    $0D,$0A

weapnChoiceGun_msg dc.b 'you have selected the gun ',0
                dc.b    $0D,$0A
weapnChoicefire_msg  dc.b ' you have chosen the fireball' ,0
                dc.b    $0D,$0A
enemyHealthmsg:  dc.b    'enemy health is :',0
                dc.b    $0D,$0A
attackmsg:      dc.b    'please enter a value to attack the rabbid :',0
                dc.b    $0D,$0A
update_msg:     dc.b    'Update Gameplay !',0
draw_msg:       dc.b    'Draw Screen !',0
hit_msg:        dc.b    'Strike! NICE ',0
                dc.b    $0D,$0A
miss_msg:       dc.b    'Miss! TRY AGAIN ',0
                dc.b    $0D,$0A
loop_msg:       dc.b    '.',0
replay_msg:     dc.b    'Enter 0 to Quit any other number to replay : ',0
hud_msg:        dc.b    'Score : ',0
endRoomOnemsg:     dc.b   'congrats you killed the rabid lets move into the next room : ',0
                dc.b    $0D,$0A
firemsg:        dc.b ' you threw a fireball',0
                dc.b    $0D,$0A
gunmsg:         dc.b ' you shot a bullet',0
                dc.b    $0D,$0A
damagemsg:      dc.b ' please choose your weapon'
                dc.b    $0D,$0A
                dc.b   ' press less than 5 for gun or 5 for the sword or greater than for fireball : ',0
                dc.b    $0D,$0A
*room two messages
roomTwo_Entermsg: dc.b 'congrats you have made it to the second room there is two rabids '
                  dc.b    $0D,$0A
                  dc.b   ' in this room kill them all to get to the boss  : ',0
                  dc.b    $0D,$0A
super_msg       dc.b 'the gates of hell open and '
                dc.b       'the enemy is dragged to the pits of tartarus ',0
                dc.b    $0D,$0A
newPower_msg dc.b 'you have recieved a new power called '
             dc.b ' hell gates use 6 to activate it'
             
ult_msg            dc.b ' press 6 to instantly delete the oposition',0
player_health_left dc.b ' the players health is :' ,0

player_heal_msg  dc.b ' you need to heal now as you self harmed'
                 dc.b ' press 1 to heal yourself ',0
                 dc.b    $0D,$0A
playerSelfHeal    dc.b ' you have healed yourself by 3 pts your health is: ',0
*boss room messages
bossRoomBeforeEnter dc.b 'you are about to enter the boss room are you ready ?'
                    dc.b    $0D,$0A
                    dc.b 'press any key to enter : '
                    dc.b    $0D,$0A
bossRoomIntro dc.b ' STOMP STOMP'
              dc.b    $0D,$0A
              dc.b ' the great rabbid trounces about his throne room'
              dc.b    $0D,$0A
              dc.b ' HE TURNS AND NOTICES YOU'
              dc.b    $0D,$0A
              dc.b ' press your keys to attack >5<',0
bossDamageTaken dc.b ' the boss has taken damage :',0
*ENDING STRINGS 
ending_msg dc.b ' you have defeated the final boss you may now reap your rewards'
            dc.b    $0D,$0A
            dc.b   '                              '
            dc.b    $0D,$0A
            dc.b ' THE GOLDEN FLEECE OF ARCADIA '
            dc.b    $0D,$0A
            dc.b ' THE SILVER BOOTS OF HERMES '
            dc.b    $0D,$0A
            dc.b ' THE GREAT EY OF OSIRIS '
            dc.b    $0D,$0A
           dc.b ' 150000000 GOLD'
           dc.b    $0D,$0A
            dc.b ' 14 SILVER '
            dc.b    $0D,$0A
            dc.b ' TWO NITRATE STATUES'
            dc.b    $0D,$0A
            dc.b ' A 3080 TI' 
            dc.b    $0D,$0A 
            dc.b ' THE THUNDER OF THOR '
            dc.b    $0D,$0A
            dc.b ' THE HEAD OF THE MIDGARD SERPANT  '
            dc.b    $0D,$0A
            dc.b ' THE TOOTH OF FENRIR'
            dc.b    $0D,$0A,0
credits_msg dc.b ' a game by donal howe c00249662 '
            dc.b    $0D,$0A
            dc.b ' thanks for playing my first assembly game ',0

health:     ds.w    1   Players Health
score:      ds.w    1   Reserve space for score

    end start













*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
