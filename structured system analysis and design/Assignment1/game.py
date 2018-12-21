from graphics.frame import *
from graphics.drawing import *
from graphics.core import *

from level import *
from mario import *

from getch import AsyncGetch

import os, time, subprocess, signal, atexit

class GameStateMachine:
    STATE_MENU = 0
    STATE_LEVEL_BEGIN = 1
    STATE_PLAYING = 2
    STATE_GAME_OVER = 4
    STATE_QUIT = 5
    STATE_GAME_FINISH = 6

    def __init__(self, target_fps = 16, window_size = Size(32, 24)):
        self.target_fps = target_fps
        self.window_size = window_size
        self.state = GameStateMachine.STATE_MENU
        self.async_key_collector = AsyncGetch()

        self.lives = 0

        self.__skipFrames = 0
        self.__level_stack = []
        self.__mario = Mario()

        self.__music_pid = None
        atexit.register(self.__kill_subprocess)      

    def __wait(self, seconds):
        self.__skipFrames = seconds * self.target_fps
    
    def __kill_subprocess(self):
        if self.__music_pid != None:
            os.kill(self.__music_pid.pid, signal.SIGTERM)
        self.__music_pid = None

    def __do_state_menu(self, buf, keys):
        info_overlay = Overlay(self.window_size)
        putRectange(info_overlay, Point(4, self.window_size.height - 4), Size(24, 5))
        text = "MARIO 1000BC"
        putText(info_overlay, text, Point(self.window_size.width/2 - len(text)/2, self.window_size.height - 6))
        text = "START GAME"
        putText(info_overlay, text, Point(self.window_size.width/2 - len(text)/2, self.window_size.height - 12))
        text = "PRESS SPACE TO START GAME"
        putText(info_overlay, text, Point(self.window_size.width/2 - len(text)/2, self.window_size.height - 14))        
        LOMountainMedium(Point(4, 3), None).draw(info_overlay)
        LOMountainLarge(Point(16, 3), None).draw(info_overlay)
        putRectange(info_overlay, Point(0, 2), Size(self.window_size.width, 2), False, '█')
        buf.add_overlay(info_overlay)

        if ' ' in keys:            
            self.lives = 3
            self.__level_stack = [Level(1, 1, self.window_size)]
            return self.STATE_LEVEL_BEGIN
        return self.STATE_MENU

    def __do_state_level_begin(self, buf, keys):
        self.__kill_subprocess()
        self.__music_pid = subprocess.Popen(["aplay", "./audio/music.wav"])

        curlevel = self.__level_stack[-1]
        curlevel.reset()
        mario = self.__mario
        mario.reset(Point(self.window_size.width/2, 6), curlevel, mario.score)   

        info_overlay = Overlay(self.window_size)
        text = "WORLD " + str(curlevel.world) + "-" + str(curlevel.level)        
        putText(info_overlay, text, Point(self.window_size.width/2 - len(text)/2, self.window_size.height/2))
        text = "LIVES x" + str(self.lives).zfill(2)
        putText(info_overlay, text, Point(self.window_size.width/2 - len(text)/2, self.window_size.height/2 - 2))
        buf.add_overlay(info_overlay)

        self.__wait(6)
        return self.STATE_PLAYING

    def __do_state_playing(self, buf, keys):
        curlevel = self.__level_stack[-1]
        mario = self.__mario
        
        key_action_map = { 'w' : Mario.ACTION_JUMP,
                           'd' : Mario.ACTION_RIGHT,
                           'a' : Mario.ACTION_LEFT }

        for key in list(set(keys)):
            if key != - 1 and key in key_action_map:
                self.__mario.do_action(key_action_map[key])

        curlevel.tick()
        mario.tick()

        levelbg_overlay = Overlay(self.window_size)
        curlevel.render(levelbg_overlay)
        buf.add_overlay(levelbg_overlay)

        mario_overlay = Overlay(self.window_size)
        mario.draw(mario_overlay)
        buf.add_overlay(mario_overlay)

        info_overlay = Overlay(self.window_size)
        putText(info_overlay, "MARIO", Point(3, self.window_size.height - 1))
        putText(info_overlay, "WORLD", Point(18, self.window_size.height - 1))
        putText(info_overlay, "TIME", Point(25, self.window_size.height - 1))
        putText(info_overlay, str(mario.score).zfill(6), Point(3, self.window_size.height - 2))        
        putText(info_overlay, "x" + str(self.lives).zfill(2), Point(12, self.window_size.height - 2))
        putText(info_overlay, str(curlevel.world) + "-" + str(curlevel.level), Point(19, self.window_size.height - 2))
        putText(info_overlay, str(curlevel.get_time_remaining()).zfill(3), Point(26, self.window_size.height - 2))
        buf.add_overlay(info_overlay)

        if curlevel.get_state() == curlevel.STATE_FINAL:
            self.__kill_subprocess()

        if curlevel.get_state() == curlevel.STATE_COMPLETE:
            self.__wait(5)
            self.__kill_subprocess()
            os.system("aplay ./audio/smb_stage_clear.wav /dev/null 2>&1 &")
            next_world = int(curlevel.config["next_world"])
            next_level = int(curlevel.config["next_level"])
            if next_world == -1 or next_level == -1:
                return self.STATE_GAME_FINISH
            self.__level_stack[-1] = Level(next_world, next_level, self.window_size)
            return self.STATE_LEVEL_BEGIN

        if curlevel.get_time_remaining() == 10:
            os.system("aplay ./audio/smb_warning.wav /dev/null 2>&1 &")

        if curlevel.get_time_remaining() <= 0 or mario.dead:
            self.__kill_subprocess()
            self.__wait(5)
            if self.lives == 0:
                return self.STATE_GAME_OVER
            self.lives = self.lives - 1
            return self.STATE_LEVEL_BEGIN
        return self.STATE_PLAYING

    def __do_state_game_over(self, buf, keys):
        curlevel = self.__level_stack[-1]
        mario = self.__mario

        info_overlay = Overlay(self.window_size)
        putText(info_overlay, "MARIO", Point(3, self.window_size.height - 1))
        putText(info_overlay, "WORLD", Point(18, self.window_size.height - 1))
        putText(info_overlay, "TIME", Point(25, self.window_size.height - 1))
        putText(info_overlay, str(mario.score).zfill(6), Point(3, self.window_size.height - 2))        
        putText(info_overlay, "x" + str(self.lives).zfill(2), Point(12, self.window_size.height - 2))
        putText(info_overlay, str(curlevel.world) + "-" + str(curlevel.level), Point(19, self.window_size.height - 2))
        putText(info_overlay, str(curlevel.get_time_remaining()).zfill(3), Point(26, self.window_size.height - 2))
        text = "GAME OVER"
        putText(info_overlay, text, Point(self.window_size.width/2 - len(text)/2, self.window_size.height/2))
        buf.add_overlay(info_overlay)

        os.system("aplay ./audio/smb_gameover.wav > /dev/null 2>&1 &")        

        self.__wait(6)
        return self.STATE_MENU

    def __do_state_game_finish(self, buf, keys):
        mario = self.__mario

        info_overlay = Overlay(self.window_size)
        text = "YOU FINISHED THE GAME!"        
        putText(info_overlay, text, Point(self.window_size.width/2 - len(text)/2, self.window_size.height/2))
        text = "YOUR SCORE: " + str(mario.score).zfill(6)
        putText(info_overlay, text, Point(self.window_size.width/2 - len(text)/2, self.window_size.height/2 - 2))
        buf.add_overlay(info_overlay)

        os.system("aplay ./audio/smb_world_clear.wav > /dev/null 2>&1 &")

        self.__wait(6)
        return self.STATE_MENU

    def run(self):
        buf = FrameBuffer(self.window_size)
        dispatch_table = { self.STATE_MENU : self.__do_state_menu,
                           self.STATE_LEVEL_BEGIN : self.__do_state_level_begin,
                           self.STATE_PLAYING : self.__do_state_playing,
                           self.STATE_GAME_OVER : self.__do_state_game_over,
                           self.STATE_GAME_FINISH : self.__do_state_game_finish }
        while self.state != self.STATE_QUIT:
            start_ms = time.time()
            keys = self.async_key_collector.getch()           

            if self.__skipFrames:
                self.__skipFrames = self.__skipFrames - 1
            else:
                buf.clear()
                self.state = dispatch_table[self.state](buf, keys)
                os.system("clear")
                buf.render()
            
            end_ms = time.time()
            frame_time = end_ms - start_ms
            if frame_time < (1/self.target_fps):
                time.sleep((1/self.target_fps) - frame_time)
