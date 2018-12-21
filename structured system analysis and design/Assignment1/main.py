from game import GameStateMachine
import sys, termios

def main ():
    try:
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)

        game_instance = GameStateMachine()    
        game_instance.run()        
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)

if __name__ == "__main__":
    main()