import React, { useState } from 'react';
import axios from 'axios';
const Balance = (props) => {
  // const { balanceFromBackend } = props;
  const [balance, setBalance] = useState('0');
  const [username, setUsername] = useState('');
  const config = {
    headers: {
      'Content-Type': 'application/json',
    },
  };
  const handleBalance = async () => {
    const ret = await axios.get('http://127.0.0.1:8000', config);
    setBalance(ret.data.balance);
  };
  return (
    <div className='balance-container'>
      <div className='balance-username-container'>
        <label className='balance-username-title'>USER NAME</label>
        <input
          className='balance-username'
          value={username}
          onChange={(e) => setUsername(e.target.value)}
        />
      </div>
      <div>
        <div className='balance-balance-container'>
          <label className='balance-balance-title'>BALANCE</label>
          <div className='balance-balance'>${balance}</div>
        </div>
      </div>
      <button className='balance-refresh-button' onClick={handleBalance}>
        Balance
      </button>
    </div>
  );
};

export default Balance;
