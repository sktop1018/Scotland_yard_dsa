import pygame
import random
import math

# Setup
WIDTH, HEIGHT = 1200, 1000  # Increased window size
NUM_NODES = 50  # Adjust if needed
NODE_RADIUS = 20  # Larger radius for visibility
EDGE_WIDTH = 3
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
YELLOW = (255, 255, 0)
PINK = (255, 105, 180)
BLUE = (173, 216, 230)

pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Scotland Yard Game - City Map")
background = pygame.image.load('bg.jpg')
background = pygame.transform.scale(background, (WIDTH, HEIGHT))

# Function to generate random positions for nodes with increased spacing
def generate_node_positions(num_nodes):
    positions = []
    for _ in range(num_nodes):
        while True:
            # Generate random coordinates within a larger area
            x = random.randint(100, WIDTH - 100)
            y = random.randint(100, HEIGHT - 100)
            
            # Check if the new node is too close to any existing nodes
            too_close = False
            for (existing_x, existing_y) in positions:
                if math.sqrt((existing_x - x) ** 2 + (existing_y - y) ** 2) < NODE_RADIUS * 2:
                    too_close = True
                    break
            
            if not too_close:
                positions.append((x, y))
                break
    return positions

# Function to draw edges
def draw_edges(graph, positions):
    for node, neighbors in graph.items():
        x1, y1 = positions[node]
        for neighbor in neighbors:
            x2, y2 = positions[neighbor]
            pygame.draw.line(screen, YELLOW, (x1, y1), (x2, y2), EDGE_WIDTH)

# Function to draw nodes
def draw_nodes(positions, detective_positions, mrxpos):
    for i, (x, y) in enumerate(positions):
        if i==mrxpos:
            pygame.draw.circle(screen, BLUE, (x, y), NODE_RADIUS)
        elif i in detective_positions:  # Check if it's a detective's position
            pygame.draw.circle(screen, PINK, (x, y), NODE_RADIUS)
        else:
            pygame.draw.circle(screen, WHITE, (x, y), NODE_RADIUS)
            pygame.draw.circle(screen, BLACK, (x, y), NODE_RADIUS, 2)

# Function to display node numbers
def display_node_numbers(positions):
    font = pygame.font.SysFont(None, 24)
    for i, (x, y) in enumerate(positions):
        text = font.render(str(i), True, BLACK)
        screen.blit(text, (x - 10, y - 10))

# Load graph data from positions.txt
def load_graph_data():
    graph = {}
    positions = []
    with open("positions.txt", "r") as file:
        file.readline()  # Skip Mr. X's position
        file.readline()  # Skip detective positions

        for line in file:
            data = list(map(int, line.strip().split(":")[1].split()))
            node = int(line.strip().split(":")[0])
            graph[node] = data
    return graph

# Load detective positions from the same file
# Load detective positions from the same file
def load_detective_positions():
    detective_positions = []
    with open("detective_positions.txt", "r") as file:
        detective_positions_line = file.readline().strip()  # Read the line containing detective positions
        detective_positions = list(map(int, detective_positions_line.split()))  # Convert to integers
    return detective_positions

def load_mrx_position():
    with open("mrx_position.txt", "r") as file:
        mrx = file.readline().strip()  # Read the line containing detective positions
    if mrx=="":
        return -1
    return int(mrx)

def load_result():
    with open("game_result.txt", "r") as file:
        result = file.readline().strip()  # Read the line containing detective positions
    return result 

# Main loop
def main():
    running = True
    graph = load_graph_data()
    detective_positions = load_detective_positions()
    positions = generate_node_positions(NUM_NODES)
    
    while running:
        screen.blit(background, (0,0))
        draw_edges(graph, positions)
        detective_positions = load_detective_positions()
        mrxpos = load_mrx_position()
        gameresult = load_result()
        # print(mrxpos)
        draw_nodes(positions, detective_positions, mrxpos)

        display_node_numbers(positions)
        if len(gameresult) != 0:
            font = pygame.font.Font(None, 100)
            text = font.render(gameresult, True, (0, 0, 0))
            text_width, text_height = text.get_size()
            padding = 20
            # Create a rectangle with padding
            rect_x = 600 - (text_width // 2) - padding
            rect_y = 500 - (text_height // 2) - padding
            rect_width = text_width + padding * 2
            rect_height = text_height + padding * 2

            # Fancy rectangle (rounded corners, border width, and fill color)
            rect = pygame.Rect(rect_x, rect_y, rect_width, rect_height)

            # Set the colors
            rect_color = (255, 223, 186)  # Light color for the rectangle
            border_color = (0, 0, 0)  # Black border color
            border_width = 3 
            pygame.draw.rect(screen, rect_color, rect)
            pygame.draw.rect(screen, border_color, rect, border_width)  # Draw the border
            text_rect = text.get_rect(center=(600, 500)) 
            screen.blit(text, text_rect)

            pygame.display.flip()
            pygame.time.wait(10000) 
            running = False
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
        
        pygame.display.flip()
        pygame.time.Clock().tick(60)

    pygame.quit()

if __name__ == "__main__":
    main()
