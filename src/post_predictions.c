#include "post_predictions.h"

void save_detections(char *image_id, int num, int width, int height, float thresh,
                     box *boxes, float **probs, char **names, int classes)
{
    FILE *fp;
    char *csv_filename;

    csv_filename = malloc(strlen("predictions_") +strlen(basename(image_id))+ strlen(".csv"));
    strcpy(csv_filename, "predictions_");
    strcat(csv_filename, basename(image_id));
    strcat(csv_filename, ".csv");

    if ((fp = fopen(csv_filename, "a")) == NULL) {
        printf("File open error: %s\n", csv_filename);
        exit(1);
    }
    fprintf(fp, "image_id,img_width,img_height,thresh,box_left,box_right,box_top,box_bottom,class_prob,class_name\n");

    int i;
    printf("num=%d\n",num);
    printf("classes=%d\n",classes);
    for (i = 0; i < num; ++i) {
        int class = max_index(probs[i], classes);
        float prob = probs[i][class];

        if (! (prob > thresh)) {
            continue;
        }

        box b = boxes[i];

        int left  = (b.x - b.w / 2.) * width;
        int right = (b.x + b.w / 2.) * width;
        int top   = (b.y - b.h / 2.) * height;
        int bot   = (b.y + b.h / 2.) * height;

        if (left < 0) left = 0;
        if (right > width - 1) right = width - 1;
        if (top < 0) top = 0;
        if (bot > height - 1) bot = height - 1;

        fprintf(fp, "%s,%d,%d,%f,%d,%d,%d,%d,%f,%s\n",
                image_id, width, height, thresh, left, right, top, bot, prob, names[class]);
    }
    fprintf(fp, " , , , , , , , , , \n");
    fclose(fp);
}
