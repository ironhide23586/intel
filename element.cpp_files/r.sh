export LD_LIBRARY_PATH=/root/sbiswas
export KMP_AFFINITY=compact

for mat_size in {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000}; do
	for cores in {1, 2, 4, 8, 16, 32, 60}; do
		for threads in {1, 2, 3, 4}; do
			export KMP_PLACE_THREADS=$cores'c,'$threads't'
			echo 'Matrix Size = '$mat_size >> report.txt
			echo 'Experiment with '$threads' threads/core on '$cores' cores' >> report.txt
			./e_inplace $mat_size >> report.txt
		done
	done
done
		
		
