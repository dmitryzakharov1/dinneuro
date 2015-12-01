#include "fann.h"
#include "parallel_fann.h"
#include "parallel_fann.c"
#include "func.h"

int main(int argc, const char* argv[])
{
	
	if (argc < 2) {
    printf("Usage: ./dinneuro filename\n");
    return -1;
	}
	
	//подготавливаем выборки
	if (csv2fann2(argv[1], 59, 50, 100, true)) { printf("Converted\n"); }
	
	//получим данные о количестве входных и выходных параметров
	int *params;
	const char * filename;
	const char * normfilename;
	filename = "data.data";
	//filename = "scaling.data";
	normfilename = "normalized.train";
	params = getparams(filename);
	
    unsigned int num_threads = omp_get_thread_num();
	float error;
	const unsigned int num_input = params[1];
	const unsigned int num_output = params[2];
	//printf("num_input=%d num_output=%d\n", num_input, num_output);
	const unsigned int num_layers = 4;
	//const unsigned int num_neurons_hidden = num_output;
	const unsigned int num_neurons_hidden = 5;
	const float desired_error = (const float) 0.0001;
	const unsigned int max_epochs = 5000;
	const unsigned int epochs_between_reports = 1000;
	struct fann_train_data * data = NULL;
	struct fann *ann = fann_create_standard(num_layers, num_input, num_neurons_hidden, num_neurons_hidden, num_output);
	fann_set_activation_function_hidden(ann, FANN_LINEAR);
	fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_training_algorithm(ann, FANN_TRAIN_RPROP);
	//printf("test\n");
	data = fann_read_train_from_file(filename);
	
	printf("Readed train from %s\n", filename);
	
	fann_set_scaling_params(
		    ann,
			data,
			-1,	/* New input minimum */
			1,	/* New input maximum */
			-1,	/* New output minimum */
			1);	/* New output maximum */

	fann_scale_train( ann, data );
	printf("Scaled\n");
	
	//сохраним нормализованную обучающу выборку в файл
	fann_save_train(data, normfilename);
	printf("Saved scaled file %s\n", normfilename);
	
	unsigned int i;
	printf("Start learning...\n");
	for(i = 1; i <= max_epochs; i++)
	{
		error = num_threads > 1 ? fann_train_epoch_irpropm_parallel(ann, data, num_threads) : fann_train_epoch(ann, data);
		//если ошибка обучения меньше или равно заданной - выходим из цикла обучения
		//if (error <= desired_error) { printf ("Desired error detected. Finishing teaching.\n"); break; }
		//если текущий счетчик делится без остатка на epochs_between_reports - пишем лог
		//if (i % epochs_between_reports == 0) { printf("Epochs     %8d. Current error: %.10f\n", i, error); }
		
	}
	printf("End learning.\n");
	printf("MSE = %f\n", fann_get_MSE(ann));

	//fann_train_on_data(ann, data, max_epochs, epochs_between_reports, desired_error);
	fann_destroy_train( data );
	fann_save(ann, "scaling.net");
	fann_destroy(ann);
	
	//проверка
	printf("Testing...\n");
	fann_type *calc_out;
	//printf("fann_length_train_data=%d\n",fann_length_train_data(data));
	printf("Creating network.\n");
	ann = fann_create_from_file("scaling.net");
	if(!ann)
	{
		printf("Error creating ann --- ABORTING.\n");
		return 0;
	}
	
	//печатаем параметры сети
	//fann_print_connections(ann);
	//fann_print_parameters(ann);
	
	printf("Testing network.\n");
	data = fann_read_train_from_file(filename);
	for(i = 0; i < fann_length_train_data(data); i++)
	{
		fann_reset_MSE(ann);
    	fann_scale_input( ann, data->input[i] );
		calc_out = fann_run( ann, data->input[i] );
		fann_descale_output( ann, calc_out );
		printf("Result %f original %f error %f or %.2f%%\n",
			calc_out[0], data->output[i][0],
			(float) fann_abs(calc_out[0] - data->output[i][0]), (100*(float) fann_abs(calc_out[0] - data->output[i][0]))/(float)calc_out[0]);
	}

	fann_destroy_train( data );
	fann_destroy(ann);

return 0;
}

