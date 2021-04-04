bash compile.sh

mkdir -p tests
mkdir -p tests/inputs
mkdir -p tests/outputs
mkdir -p tests/images

start_c=0
end_c=10
step_val=1
version_num=1
func_name="log_x__varied__c__exp__10"
folder_name=$start_c"__"$step_val"__"$end_c"__ver$version_num""__$func_name"

echo $folder_name

mkdir -p tests/inputs/$folder_name
mkdir -p tests/outputs/$folder_name
mkdir -p tests/images/$folder_name

for (( i=$start_c; i<=$end_c; i+=$step_val ))
do

	./build/test_case_generator.o $i tests/inputs/$folder_name/in$i.txt
	echo "> Generated Input @ tests/inputs/in$i.txt"

	./build/daaaaaa tests/inputs/$folder_name/in$i.txt tests/outputs/$folder_name/out$i.txt
	echo "> Generated Output @ tests/outputs/out$i.txt"

	python3 ./plot_output.py -i ./tests/inputs/$folder_name/in$i.txt -o ./tests/outputs/$folder_name/out$i.txt -g ./tests/images/$folder_name/image$i.png
done