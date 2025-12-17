import matplotlib.pyplot as plt
import glob
from matplotlib.ticker import AutoMinorLocator
import numpy as np

def plot_sorting_times(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()
    
    n_values = []
    a_times = []
    b_times = []
    
    for line in lines:
        parts = line.strip().split()
        
        if len(parts) < 3:
            continue
        
        try:
            n_val = int(parts[0])
            n_values.append(n_val)
            a_times.append(float(parts[1]))
            b_times.append(float(parts[2]))
        except (ValueError, IndexError):
            continue
    
    plt.figure(figsize=(12, 7))
    
    plt.plot(n_values, a_times, 'b-', linewidth=2, label='A_Quick')
    plt.plot(n_values, b_times, 'r-', linewidth=2, label='B_Heap3')
    
    ax = plt.gca()
    
    
    plt.ylabel('Время выполнения (секунды)', fontsize=12)
    
    if "experiment_3_1" in filename:
        plt.title('Эксперимент 3.1: Время выполнения от количества n', fontsize=14, pad=20)
        plt.xlabel('n', fontsize=12)

        if n_values:
            tick_positions = []
            tick_labels = []
            
            min_n = min(n_values)
            max_n = max(n_values)
            
            step = max(1, (max_n - min_n) // 10) 
            
            for n in range(min_n, max_n + 1, step):
                if n >= min_n:
                    tick_positions.append(n)
                    if n == 1:
                        tick_labels.append('1')
                    else:
                        k = (n - 1) // 10000
                        tick_labels.append(f'{k}·10⁴+1')
            
            ax.set_xticks(tick_positions)
            ax.set_xticklabels(tick_labels, rotation=45, fontsize=9)
    
    elif "experiment_3_2" in filename:
        plt.title('Эксперимент 3.2: Время выполнения от q = w', fontsize=14, pad=20)
        plt.xlabel('q_w', fontsize=12)

        if n_values:
            tick_positions = []
            tick_labels = []
            
            min_n = min(n_values)
            max_n = max(n_values)
            
            step = 100000
            
            for q in range(0, max_n + 1, step):
                if q >= min_n:
                    tick_positions.append(q)
                    k = q // 10000
                    if k == 0:
                        tick_labels.append('0')
                    else:
                        tick_labels.append(f'{k}·10⁴')
            
            ax.set_xticks(tick_positions)
            ax.set_xticklabels(tick_labels, rotation=45, fontsize=9)
    
    else:
        plt.title('Сравнение времени выполнения алгоритмов', fontsize=14, pad=20)
    

    all_times = a_times + b_times
    max_time = max(all_times)
    
    max_time_adjusted = np.ceil(max_time / 0.25) * 0.25
    
    ax.set_ylim(bottom=0, top=max_time_adjusted)
    
    y_ticks = np.arange(0, max_time_adjusted + 0.25, 0.25)
    ax.set_yticks(y_ticks)
    
    ax.yaxis.set_major_formatter(plt.FuncFormatter(lambda x, p: f'{x:.2f}'))

    plt.grid(True, which='major', alpha=0.5, linestyle='-', linewidth=0.8, color='gray')
    plt.minorticks_on()
    plt.grid(True, which='minor', alpha=0.2, linestyle='--', linewidth=0.5, color='gray')
    
    ax.xaxis.set_minor_locator(AutoMinorLocator(5))
    ax.yaxis.set_minor_locator(AutoMinorLocator(5))
    
    plt.legend(fontsize=10, loc='best', framealpha=0.9)
    
    plt.tight_layout()
    
    output_filename = filename.replace('.txt', '_graph.png')
    plt.savefig(output_filename, dpi=150, bbox_inches='tight')
    
    plt.show()


if __name__ == "__main__":
    txt_files = glob.glob('*.txt')
    for file in sorted(txt_files): 
        plot_sorting_times(file)