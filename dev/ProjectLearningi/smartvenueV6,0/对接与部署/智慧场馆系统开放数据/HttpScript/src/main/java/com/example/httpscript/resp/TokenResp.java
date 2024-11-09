package com.example.httpscript.resp;

import lombok.Data;

@Data
public class TokenResp {
    private int code;
    private String message;
    private String description;
    private String uuid;
    private Result result;

    @Data
    public static class Result {
        private String access_token;
        private String token_type;
        private String expires_in;
        private String scope;
        private String license;
    }
}
