package com.example.httpscript.resp;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

import java.util.List;

@Data
public class PostStuMajorResp {
    private int code;
    private String message;
    private String description;
    private String uuid;
    private Result result;

    // Getters and setters

    @Data
    public static class Result {
        private int page;
        private int per;
        private int total;
        private int maxPage;
        private DataStruct dataStruct;
        private List<Data> data;

        @JsonProperty("max_page")
        public void setMaxPage(int maxPage) {
            this.maxPage = maxPage;
        }

        // Getters and setters

        public static class DataStruct {
            private String ZYBM;
            private String ZYMC;
            private String YXBM;

            // Getters and setters
        }

        @lombok.Data
        public static class Data {
            @JsonProperty("ZYBM")
            private String ZYBM;
            @JsonProperty("ZYMC")
            private String ZYMC ;
            @JsonProperty("YXBM")
            private String YXBM;

            // Getters and setters
        }
    }
}

