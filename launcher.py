import subprocess
import threading

def run_cpp():
    subprocess.run(["./main.exe"])  # Adjust based on your compiled C++ binary name

def run_graphics():
    import graphics  # Ensure `graphics.py` is in the same directory
    graphics.main()

if __name__ == "__main__":
    cpp_thread = threading.Thread(target=run_cpp)
    graphics_thread = threading.Thread(target=run_graphics)

    cpp_thread.start()
    graphics_thread.start()

    cpp_thread.join()
    graphics_thread.join()
