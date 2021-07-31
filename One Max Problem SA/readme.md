# Simulated Annealing

* 主程式: `main.exe`

    * usage: 

        ```bash
        main.exe BIT_SIZE ITERATION RUN INIT_TEMP TEMP_COOLDOWN_RATE NB_TYPE F_TYPE N RESULT_PATH
        # neighbor type => 0: B2D neighbor / 1: onebit-flip neighbor
        # fitness type => 0: one max problem / 1: deception problem
        ```

    

* 51run 結果平均收斂圖: /result/*.jpg

* 結果分析:

    兩種transition的方法(十進位neighbor / 隨機反轉bit) 的結果差不多，但使用爬山時隨機反轉bit的結果明顯較好(幾乎能達到最佳解)。觀察實驗結果可能是溫度跟下降係數沒有調整好，導致很快就收斂到區域最佳解
