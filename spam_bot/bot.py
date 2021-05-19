import pyautogui
import time

time.sleep(5)

for i in range(1000):
    pyautogui.write("<3", interval=0)
    pyautogui.press("enter")
