#/bin/bash

# how many frames to run the benchmark
NUM_FRAMES="100"

#can be true or false
FULLSCREEN="true"

#screen/window resolution
WIDTH="1920"
HEIGHT="1200"

# 0 means tell SDL (or Qt) to disable vsync
SWAP_INTERVAL="0"

# number of cells in each dimension to draw
NUM_CELLS_X="25"
NUM_CELLS_Y="12"

# virtual size of table, display is zoomed out to show
# entire table.
TABLE_WIDTH="4000"
TABLE_HEIGHT="2000"

# for Qt's -geometry bits
WIDTH_HEIGHT="$WIDTH""x""$HEIGHT"

common_options="fullscreen $FULLSCREEN swap_interval $SWAP_INTERVAL add_image /usr/share/games/blobwars/gfx/ num_cells_x $NUM_CELLS_X num_cells_y $NUM_CELLS_Y table_width $TABLE_WIDTH table_height $TABLE_HEIGHT num_frames $NUM_FRAMES num_skip_frames 3 init_table_rotating true init_table_clipped true init_cell_rotating true num_background_colors 100 text_colors_opaque false"


function run_benchmark {
    echo "vblank_mode=0 $1 $common_options ${@:2}"
    vlank_mode=0 $1 $common_options ${@:2}
}

run_benchmark $1 "width $WIDTH height $HEIGHT -geometry $WIDTH_HEIGHT ${@:2}"
#run_benchmark ./painter-cells-GLES-release "width $WIDTH height $HEIGHT" fastuidraw-ES-results.txt
