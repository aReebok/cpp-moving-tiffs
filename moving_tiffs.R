# written by Ariz Mohammad 

rm(list = ls())
csv_file <- "/run/media/areeba/New Volume/Acad/Image_analysis/2021/Sheath_cell_project/06.17.2021_DG5249_GFP_OLLAS_MSP/06.17.2021_DG5249_GFP_OLLAS_MSP.csv"
a = read.csv(file = csv_file, header = T, sep = ",", na.strings = "", stringsAsFactors = FALSE)

dir_path <- paste0(dirname(csv_file), .Platform$file.sep)
dir_path <- "/run/media/areeba/images/06.17.2021_DG5249_GFP_OLLAS_MSP/"


for (i in 2:ncol(a)){
  print(table(a[i]))
}

# a[a=="p"] <- "PROM-1_HA"
# a[a=="g"] <- "PROM-1_HA_gld-2_gld-1_fbf-1_fbf-2"
a[a=="n"] <- "N2"
a[a=="6"] <- "SYGL-1_OLLAS_DG5136"
a[a=="9"] <- "SYGL-1_OLLAS_DG5249"
#a[a=="glp-1"] <- "gld-2_gld-1_glp-1_FBF-2_V5"
a$no <- as.character(a$no)
a$no <- paste0(stringr::str_pad(string = a$no, width = 3, pad = "0", side = "left"), "-", stringr::str_pad(string = as.character(as.integer(a$no)+1), width = 3, pad = "0", side = "left"), ".tif")

colnames(a) <- c("tifs", paste0("replicate_", as.character(1:(ncol(a)-1))))

for (i in 2: ncol(a)){
  temp_data <- a[,c(1, i)]
  temp_data <- temp_data[complete.cases(temp_data), ]
  columns <- colnames(temp_data)
  replicate_no <- columns[2]
  replicate_dir <- paste0(dir_path, replicate_no)
  stitched_dir <- list.files(path = replicate_dir, full.names = TRUE, recursive = TRUE, pattern = "stitched_images", include.dirs = TRUE)
  stitched_dir <- stitched_dir[file.info(stitched_dir)$isdir]
  dir_names <- unique(temp_data[,2])
  for (dir in dir_names){
    dir.create(paste0(stitched_dir, "/", dir))
  }
  for (j in 1:nrow(temp_data)){
    tif_name <- temp_data[j,1]
    tif_to_move <- paste0(stitched_dir, "/", tif_name)
    moved_tif <- paste0(stitched_dir, "/", temp_data[j,2], "/", tif_name)
    if (file.exists(tif_to_move)){
      file.rename(tif_to_move, moved_tif)
    }else{
      print(paste(tif_to_move, "does not exist"))
    }
  }
}

