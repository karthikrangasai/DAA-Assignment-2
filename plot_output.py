import numpy as np
import matplotlib.pyplot as plt
import argparse


def plot_data(input_file, output_file, image_name):
    input_points = []
    with open(input_file, 'r') as f:
        for line in f:
            line = line.strip(' \n')
            if len(line.split()) == 2:
                point = [float(i) for i in line.split()]
                input_points.append(point)
    input_points = np.array(input_points)
    plt.scatter(input_points[:, 0], input_points[:, 1], color='black', s=5)

    # points = []
    count = 0
    with open(output_file, 'r') as f:
        for line in f:
            line = line.strip(' \n')
            data = [float(i) for i in line.split()]
            x = [data[0], data[2]]
            y = [data[1], data[3]]
            # color = tuple(np.random.rand(3))
            if count == 0:
                plt.plot(x, y, color='red')
                count = 1
            else:
                plt.plot(x, y, color='green')
                count = 0
            # points.append(data)

    # points = np.array(points)
    # assert len(points.shape) == 2
    # for i in range(points.shape[0]-1):
    #     x = [points[i][0], points[i+1][0]]
    #     y = [points[i][1], points[i+1][1]]
    #     color = tuple(np.random.rand(3))
    #     plt.plot(x, y, color=color)

    # plt.show()
    plt.savefig(image_name, dpi=200)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-i', '--input_file', type=str, required=True,
                        help='Path to input text file')
    parser.add_argument('-o', '--output_file', type=str, required=True,
                        help='Path to output text file')
    parser.add_argument('-g', '--image_file', type=str, required=True,
                        help='Path to where plot must be saved')
    args = vars(parser.parse_args())
    plot_data(input_file=args['input_file'],
              output_file=args['output_file'],
              image_name=args['image_file'])
